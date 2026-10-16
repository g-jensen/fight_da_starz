#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "window.h"
#include "terminal.h"
#include "point.h"
#include "core.h"
#include "sys.h"

void window_buf_draw(struct draw_buf *draw_buf) {
    write(STDOUT_FILENO, draw_buf->b, draw_buf->length);
}

int window_mmap(window *window, size_t window_drawbuf_capacity) {
    char *window_drawbuf = memory_map(window_drawbuf_capacity);
    window->drawBuf = (draw_buf){.b = window_drawbuf, .length = 0, .capacity = window_drawbuf_capacity};
    return 0;
}

int insert_string(draw_buf *draw_buf, size_t *draw_buf_length, char* string) {
    char c;
    int i;
    for (i = 0; (c = string[i]) != '\0'; i++) {
        if (*draw_buf_length < draw_buf->capacity) {
            draw_buf->b[(*draw_buf_length)++] = c;
        } else {
            return -1;
        }
    }
    return 0;
}

int window_buf_reset_cursor(draw_buf *draw_buf, size_t *draw_buf_length) {
    return insert_string(draw_buf, draw_buf_length, RESET_CURSOR);
}

int window_buf_clear_line(draw_buf *draw_buf, size_t *draw_buf_length) {
    return insert_string(draw_buf, draw_buf_length, CLEAR_LINE);
}

int window_buf_new_line(draw_buf *draw_buf, size_t *draw_buf_length) {
    return insert_string(draw_buf, draw_buf_length, NEW_LINE);
}

int grid_index_into_drawbuf(grid *grid, size_t grid_index, draw_buf *draw_buf, size_t grid_length) {
    size_t draw_buf_length = draw_buf->length;
    if (grid_index == 0) {
        if (window_buf_reset_cursor(draw_buf,&draw_buf_length) == -1) {
            return -1;
        }
    }
    int col_offset = grid_index % grid->cols;
    if (col_offset == 0) {
        if (window_buf_clear_line(draw_buf,&draw_buf_length) == -1) {
            return -1;
        }
    }

    static char color_escape_code[ESCAPE_CODE_CAPACITY];
    color_to_escape_code(color_escape_code, &grid->colors[grid_index]);

    if (insert_string(draw_buf, &draw_buf_length, color_escape_code) == -1) {
        return -1;
    }
    if (draw_buf_length < draw_buf->capacity) {
        draw_buf->b[draw_buf_length++] = grid->chars[grid_index];
    } else {
        return -1;
    }
    if (insert_string(draw_buf, &draw_buf_length, "\033[0;0m") == -1) {
        return -1;
    }
    
    if (col_offset == grid->cols-1 && grid_index < grid_length-1) {
        if (window_buf_new_line(draw_buf, &draw_buf_length) == -1) {
            return -1;
        }
    }

    draw_buf->length = draw_buf_length;
    return 0;
}

int grid_into_drawbuf(grid *grid, size_t *grid_index, draw_buf *draw_buf) {
    size_t grid_length = grid->cols*grid->rows;
    while (*grid_index < grid_length) {
        if (grid_index_into_drawbuf(grid, *grid_index, draw_buf, grid_length) == -1) {
            return -1;
        } else {
            (*grid_index)++;
        }
    }
    return 0;
}

void window_draw(window *window, grid *grid) {
    size_t grid_index = 0;
    int result;
    do {
        window->drawBuf.length = 0;
        result = grid_into_drawbuf(grid, &grid_index, &window->drawBuf);
        window_buf_draw(&window->drawBuf);
    } while (result == -1);
}