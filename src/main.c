#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"
#include "log.h"
#include "sys.h"

#define MUS_PER_TICK MS_PER_TICK * 1000
#define MS_PER_TICK 34 // ticks per second = 1000/MS_PER_TICK

#ifdef _DEV
#include "log.h"
#endif

void render_state_to_window(struct gameState *state, struct window *window, struct grid *render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

void pace_tick(long start_time, long end_time) {
    musleep(MUS_PER_TICK - (end_time - start_time));
}

int main() {
    struct window window;
    if (window_mmap(&window) == -1) {
        die("window_mmap");
    }
    
    struct grid render_grid;
    grid_mmap(&render_grid, window.rows, window.cols);
    
    struct resources resources;
    resources_init(&resources);

    struct gameState state = game_init(&resources);
    long mus_read_timeout = 5000;
    long start_time;
    
    #ifdef _DEV
    log_info("dev mode active!");
    #endif

    window_init(); // window_init() and window_shutdown() don't really have anything to do with the 'window' abstraction. Maybe rename to terminal_init() and _shutdown()
    atexit(window_shutdown);
    while (!state.stop) {
        start_time = get_time_mus();
        update_state(&state, window_read_char(mus_read_timeout));
        render_state_to_window(&state,&window,&render_grid);
        pace_tick(start_time,get_time_mus());
    }

    return 0;
}