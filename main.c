#include "drawbuf.h"
#include "raw_mode.h"
#include "window.h"
#include "grid.h"
#include "core.h"
#include "point.h"
#include "game.h"
#include "render.h"

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols, DEFAULT_CHAR);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);
    
    struct gameState state = {
        .counter = 1, 
        .stop = 0, 
        .player_position = {.x = 0, .y = 0},
        .box_position = {.x = 0, .y = 5} 
    };
    
    window_hide_cursor();
    while (!state.stop) {
        render_state_into_grid(&state,grid);
        window_grid_draw(grid,drawBuf);
        process_key(&state);
    }
    window_show_cursor();
    drawbuf_free(&drawBuf);
    grid_free(grid);
    window_clear_screen();

    return 0;
}