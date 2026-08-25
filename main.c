#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"

void render_state_to_window(struct gameState *state, struct window window, struct grid render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

int main() {    
    struct window window = window_create();
    struct grid render_grid = render_grid_create(window.rows,window.cols);
    struct gameState state = game_init();

    window_init();
    atexit(window_shutdown);
    while (!state.stop) {
        render_state_to_window(&state,window,render_grid);
        process_key(&state, window_read_key());
    }

    window_free(window);
    grid_free(render_grid);

    return 0;
}