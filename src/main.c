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
#include <mcheck.h>
#endif

void render_state_to_window(game_state *state, window *window, grid *render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

void pace_tick(long start_time, long end_time) {
    musleep(MUS_PER_TICK - (end_time - start_time));
}
// #include <assert.h>
int main() {
    // draw_buf db;
    
    // char buf_5[5];
    // db = (draw_buf){.b = buf_5, .length = 0, .capacity = 5};
    // assert(!insert_string(&db, "DONT SHOW UP"));
    // window_buf_draw(&db);
    
    // char buf_7[7];
    // db = (draw_buf){.b = buf_7, .length = 0, .capacity = 7};
    // assert(insert_string(&db, "SHOW UP"));
    // window_buf_draw(&db);

    // char buf_12[12];
    // db = (draw_buf){.b = buf_12, .length = 0, .capacity = 12};
    // assert(insert_string(&db, "SHOW UP"));
    // assert(insert_string(&db, "AGAIN"));
    // window_buf_draw(&db);

    // char buf_14[14];
    // db = (draw_buf){.b = buf_14, .length = 0, .capacity = 14};
    // assert(insert_string(&db, "SHOW UP"));
    // assert(!insert_string(&db, "NOT AGAIN"));
    // window_buf_draw(&db);

    // return 0;
    
    #ifdef _DEV
    mtrace();
    atexit(muntrace);
    log_info("dev mode active!");
    #endif

    window window;
    if (window_mmap(&window) == -1) {
        die("window_mmap");
    }
    
    grid render_grid;
    grid_mmap(&render_grid, window.rows, window.cols);
    
    resources resources;
    resources_init(&resources);

    game_state state = game_init(&resources);
    long mus_read_timeout = 5000;
    long start_time;

    window_init(); // window_init() and window_shutdown() don't really have anything to do with the 'window' abstraction. Maybe rename to terminal_init() and _shutdown()
    atexit(window_shutdown);
    // while (!state.stop) {
        start_time = get_time_mus();
        update_state(&state, window_read_char(mus_read_timeout));
        render_state_to_window(&state,&window,&render_grid);
        pace_tick(start_time,get_time_mus());
    // }

    return 0;
}