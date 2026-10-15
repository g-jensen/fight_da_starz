#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "window.h"
#include "raw_mode.h"
#include "point.h"
#include "core.h"
#include "sys.h"

void window_hide_cursor() {
    write(STDOUT_FILENO, HIDE_CURSOR, 6);
}

void window_show_cursor() {
    write(STDOUT_FILENO, SHOW_CURSOR, 6);
}

void window_reset_cursor() {
    write(STDOUT_FILENO, RESET_CURSOR, 3);
}

void window_clear_screen() {
    write(STDOUT_FILENO, CLEAR_SCREEN, 4);
    window_reset_cursor();
}

void window_init() {
    enable_raw_mode();
    window_hide_cursor();
}

void window_shutdown() {
    window_show_cursor();
    window_clear_screen();
    disable_raw_mode();
}

optional_char window_read_char(long mus_timeout) {
    int nread;
    char c;
    nread = read_timeout(STDIN_FILENO, &c, 1, mus_timeout);
    if (nread == 0) return (optional_char){.some = 0};
    if (nread == -1 && errno != EAGAIN) die("read");
    return (optional_char){.some = 1, .value = c};
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
    if (get_terminal_size(rows,cols) == -1 || *cols == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // set cursor position to 999,999. And actually, I think this is broken.
        return window_get_cursor_pos(rows, cols);
    }
    return 0;
}

void window_buf_draw(struct draw_buf *draw_buf) {
    write(STDOUT_FILENO, draw_buf->b, draw_buf->length);
}

int window_drawbuf_capacity(int rows, int cols) {
    // return rows*cols + rows*strlen(CLEAR_LINE) + (rows-1)*strlen(NEW_LINE) + strlen(RESET_CURSOR) + 1;
    return 1024;
}

int window_mmap(window *window) {
    char *window_drawbuf;
    if (window_get_size(&window->rows, &window->cols) == -1) {
        return -1;
    }
    int window_drawbuf_cap = window_drawbuf_capacity(window->rows, window->cols);
    window_drawbuf = memory_map(window_drawbuf_cap*sizeof(char));
    window->drawBuf = (draw_buf){.b = window_drawbuf, .length = 0, .capacity = window_drawbuf_cap};
    return 0;
}

int insert_string(draw_buf *draw_buf, char* string) {
    char c;
    int i;
    for (i = 0; (c = string[i]) != '\0'; i++) {
        int buf_index = draw_buf->length+i;
        if (buf_index < draw_buf->capacity) {
            draw_buf->b[buf_index] = c;
        } else {
            return -1;
        }
    }
    draw_buf->length += i;
    return 0;
}

int window_buf_reset_cursor(draw_buf *draw_buf) {
    return insert_string(draw_buf, RESET_CURSOR);
}

int window_buf_clear_line(draw_buf *draw_buf) {
    return insert_string(draw_buf, CLEAR_LINE);
}

int window_buf_new_line(draw_buf *draw_buf) {
    return insert_string(draw_buf, NEW_LINE);
}

int grid_index_into_drawbuf(grid *grid, int grid_index, draw_buf *draw_buf) {
    if (grid_index == 0) {
        if (window_buf_reset_cursor(draw_buf) == -1) {
            return -1;
        }
    }
    int col_offset = grid_index % grid->cols;
    if (col_offset == 0) {
        if (window_buf_clear_line(draw_buf) == -1) {
            return -1;
        }
    }

    static char color_escape_code[ESCAPE_CODE_CAPACITY];
    color_to_escape_code(color_escape_code, grid->colors[grid_index]);

    if (insert_string(draw_buf, color_escape_code) == -1) {
        return -1;
    }
    if (draw_buf->length < draw_buf->capacity) {
        draw_buf->b[draw_buf->length++] = grid->chars[grid_index];
    } else {
        return -1;
    }
    if (insert_string(draw_buf, "\033[0m") == -1) {
        return -1;
    }
    
    if (col_offset == grid->cols - 1) {
        if (window_buf_new_line(draw_buf) == -1) {
            return -1;
        }
    }
    return 0;
}

int grid_into_drawbuf(grid *grid, int *grid_index, draw_buf *draw_buf) {
    while (*grid_index < grid->cols*grid->rows) {
        if (grid_index_into_drawbuf(grid, *grid_index, draw_buf) == -1) {
            return -1;
        } else {
            (*grid_index)++;
        }
    }
    return 0;
}

void window_draw(window *window, grid *grid) {
    int grid_index = 0;
    window->drawBuf.length = 0;
    while (grid_into_drawbuf(grid, &grid_index, &window->drawBuf) == -1) {
        window_buf_draw(&window->drawBuf);
        window->drawBuf.length = 0;
    }
}