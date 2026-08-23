#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "window.h"
#include "core.h"

int window_buf_reset_cursor(char* buf) {
    return insert_string(buf,RESET_CURSOR);
}

int window_buf_clear_line(char* buf) {
    return insert_string(buf,CLEAR_LINE);
}

int window_buf_new_line(char* buf) {
    return insert_string(buf,NEW_LINE);
}

void window_reset_cursor() {
    write(STDOUT_FILENO, RESET_CURSOR, 3);
}

void window_clear_screen() {
    write(STDOUT_FILENO, CLEAR_SCREEN, 4);
    window_reset_cursor();
}

void clear_and_die(const char *s) {
    window_clear_screen();
    die(s);
}

struct optional_char window_read_key() {
    int nread;
    char c;
    nread = read(STDIN_FILENO, &c, 1);
    if (nread == 0) return (struct optional_char){.some = 0};
    if (nread == -1 && errno != EAGAIN) clear_and_die("read");
    return (struct optional_char){.some = 1, .value = c};
}

int window_get_cursor_pos(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, GET_CURSOR_POS, 4) != 4) return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

    if (buf[0] != ESCAPE_0 || buf[1] != ESCAPE_1) return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
    return 0;
}

int window_get_size(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // set cursor position to 999,999
        return window_get_cursor_pos(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

void window_hide_cursor() {
    write(STDOUT_FILENO, HIDE_CURSOR, 6);
}

void window_show_cursor() {
    write(STDOUT_FILENO, SHOW_CURSOR, 6);
}

void window_buf_draw(struct drawBuf *drawBuf) {
    write(STDOUT_FILENO, drawBuf->b, drawBuf->len);
}

void window_init_config(struct windowConfig *cfg) {
    if (window_get_size(&cfg->screenrows, &cfg->screencols) == -1) {
        clear_and_die("window_get_size");
    }
}

void grid_into_drawbuf(struct grid grid, struct drawBuf drawBuf) {
    int i = 0;
    i += window_buf_reset_cursor(drawBuf.b+i);
    for (int y = 0; y < grid.rows; y++) {
        i += window_buf_clear_line(drawBuf.b+i);
        for (int x = 0; x < grid.cols; x++) {
            drawBuf.b[i++] = grid_get(grid,y,x);
        }
        if (y < grid.rows - 1) {
            i += window_buf_new_line(drawBuf.b+i);
        }
    }
}

struct drawBuf drawbuf_create_from_grid(struct grid grid) {
    int len = grid.rows*grid.cols + grid.rows*(strlen(CLEAR_LINE) + strlen(NEW_LINE)) + strlen(RESET_CURSOR);
    struct drawBuf drawBuf = {.b = malloc(len*sizeof(char)), .len = len};
    return drawBuf;
}

void window_grid_draw(struct grid grid, struct drawBuf drawBuf) {
    grid_into_drawbuf(grid,drawBuf);
    window_buf_draw(&drawBuf);
}