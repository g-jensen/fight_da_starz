#include "drawbuf.h"
#include "raw_mode.h"
#include "window.h"
#include "grid.h"

struct gameState {
    int stop;
    int counter;
};

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
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);

    struct gameState state = {.counter = 1, .stop = 0};

    window_hide_cursor();
    while (!state.stop) {
        window_grid_draw(grid,drawBuf);
        process_key(&state,grid);
    }
    window_show_cursor();
    drawbuf_free(&drawBuf);
    grid_free(grid);
    window_clear_screen();

    return 0;
}