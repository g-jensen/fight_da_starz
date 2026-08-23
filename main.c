#include "drawbuf.h"
#include "raw_mode.h"
#include "window.h"
#include "grid.h"
#include "core.h"

#define DEFAULT_CHAR ' '

struct point {
    int x;
    int y;
};

struct gameState {
    int stop;
    int counter;
    struct point player_position;
    struct point box_position;
};

void process_key(struct gameState *state) {
    struct optional_char c = window_read_key();
    if (!c.some) return;
    switch (c.value) {
        case 'w':
            state->player_position.y--;
            break;
        case 'a':
            state->player_position.x--;
            break;
        case 's':
            state->player_position.y++;
            break;
        case 'd':
            state->player_position.x++;
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

void place_char(struct point p, struct grid grid, char c) {
    if(!(p.x >= grid.cols || p.y >= grid.rows || p.x < 0 || p.y < 0)){
        grid_set(grid, p.y, p.x, c);
    }
}

void state_to_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);
    
    place_char(state->box_position, grid, '9');
    place_char(state->player_position, grid, 'o');
}

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols, DEFAULT_CHAR);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);
    
    struct gameState state = {
        .counter = 1, 
        .stop = 0, 
        .player_position = {.x = grid.cols/2, .y = grid.rows/2},
        .box_position = {.x = 0, .y = grid.rows/2} 
    };
    
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