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

#include <sys/mman.h> // breaks on windows

int main() {
    struct window window;
    if (window_get_size(&window.rows, &window.cols) == -1) {
        die("window_get_size");
    }
    int window_drawbuf_len = window_drawbuf_length(window.rows, window.cols);
    char* window_drawbuf = mmap(NULL, window_drawbuf_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    window.drawBuf = (struct drawBuf){.b = window_drawbuf, .length = window_drawbuf_len, .capacity = window_drawbuf_len};

    struct grid render_grid = render_grid_create(window.rows,window.cols);
    struct gameState state = game_init();
    long mus_read_timeout = 5000;
    long start_time;

    #ifdef _DEV
    log_info("dev mode active!");
    #endif

    window_init();
    atexit(window_shutdown);
    while (!state.stop) {
        start_time = get_time_mus();
        update_state(&state, window_read_char(mus_read_timeout));
        render_state_to_window(&state,&window,&render_grid);
        pace_tick(start_time,get_time_mus());
    }
    game_shutdown(&state);
    grid_free(&render_grid);

    return 0;
}