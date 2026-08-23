#include "drawbuf.h"
#include "raw_mode.h"
#include "window.h"
#include "grid.h"
#include "core.h"

struct gameState {
    int stop;
    int counter;
    char display_char;
};

void process_key(struct gameState *state) {
    struct optional_char c = window_read_key();
    if (!c.some) return;
    switch (c.value) {
        case 'g':
            state->display_char += 1;
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

void state_to_grid(struct gameState *state, struct grid grid) {
    for (size_t i = 0; i < grid.rows*grid.cols; i++) {
        grid.chars[i] = state->display_char;
    }
}

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);
    
    struct gameState state = {.counter = 1, .stop = 0, .display_char = '!'};
    
    window_hide_cursor();
    while (!state.stop) {
        state_to_grid(&state,grid);
        window_grid_draw(grid,drawBuf);
        process_key(&state);
    }
    window_show_cursor();
    drawbuf_free(&drawBuf);
    grid_free(grid);
    window_clear_screen();

    return 0;
}