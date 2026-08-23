#include <stdio.h>
#include <string.h>

#include "core.h"
#include "drawbuf.h"
#include "raw_mode.h"
#include "window.h"
#include "grid.h"

struct gameState {
    int stop;
    int counter;
};

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

void process_key(struct gameState *state, struct grid grid) {
    char c = window_read_key();
    switch (c) {
        case 'g':
            for (size_t i = 0; i < grid.rows*grid.cols; i++) {
                grid.chars[i] += 1;
            }
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);

    struct gameState state = {.counter = 1, .stop = 0};
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);
    
    window_hide_cursor();
    while (!state.stop) {
        grid_into_drawbuf(grid,drawBuf);
        window_draw_screen(&drawBuf);
        process_key(&state,grid);
    }
    window_show_cursor();
    drawbuf_free(&drawBuf);
    grid_free(grid);
    window_clear_screen();

    return 0;
}