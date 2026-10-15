#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"
#include "log.h"
#include "sys.h"

#define MUS_PER_TICK MS_PER_TICK * 1000
#define MS_PER_TICK 34 // ticks per second = 1000/MS_PER_TICK

#define WINDOW_DRAWBUF_CAPACITY 1024

#ifdef _DEV
#include "log.h"
#include <mcheck.h>
#endif

void render_state_to_window(game_state *state, window *window, grid *render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

void pace_tick(long start_time, long end_time) {
    long duration = (end_time - start_time);
    if (MUS_PER_TICK > duration) {
        musleep(MUS_PER_TICK - duration);
    }
}

int main() {    
    #ifdef _DEV
    mtrace();
    atexit(muntrace);
    log_info("dev mode active!");
    #endif

    window window;
    window_mmap(&window, WINDOW_DRAWBUF_CAPACITY*sizeof(*window.drawBuf.b));
    if (window_get_size(&window.rows, &window.cols) == -1) {
        die("window_get_size");
    }
    
    grid render_grid;
    grid_mmap(&render_grid, window.rows, window.cols);
    
    resources resources;
    resources_init(&resources);

    game_state state;
    game_init(&state, &resources);
    long mus_read_timeout = 5000;
    long start_time;

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