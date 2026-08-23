#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "window.h"
#include "core.h"

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

char window_read_key() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) clear_and_die("read");
    }
    return c;
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

void window_draw_screen(struct drawBuf *drawBuf) {
    write(STDOUT_FILENO, drawBuf->b, drawBuf->len);
}

void window_init_config(struct windowConfig *cfg) {
    if (window_get_size(&cfg->screenrows, &cfg->screencols) == -1) {
        clear_and_die("window_get_size");
    }
}
