#include "drawbuf.h"
#include "window.h"
#include "grid.h"
#include "core.h"
#include "point.h"
#include "game.h"
#include "render.h"

int main() {    
    struct windowConfig cfg = window_init_config(); // should return a windowConfig to align with the styles below
    
    struct grid grid = grid_create(cfg.screenrows,cfg.screencols, DEFAULT_CHAR);
    struct drawBuf drawBuf = drawbuf_create_from_grid(grid);
    // Abstract grid + drawBuf logic into "renderState", which is all that this user sees.
    // Importantly, this decouples the render state from the window: "what to render" vs "how to render".
    // Window shouldn't know that grid exists: only that renderState exists.
    // This user also shouldn't know that a grid exists.

    struct gameState state = game_init();
    
    window_init();
    while (!state.stop) {
        render_state_into_grid(&state,grid);
        window_grid_draw(grid,drawBuf); // window_draw(render_state)
        process_key(&state, window_read_key());
    }
    window_cleanup();
    drawbuf_free(&drawBuf); // render_state_cleanup()
    grid_free(grid); // render_state_cleanup()

    return 0;
}