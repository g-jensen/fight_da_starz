#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"
#include "log.h"

#include <sys/time.h>
#include <unistd.h>

#define US_PER_TICK MS_PER_TICK * 1000
#define MS_PER_TICK 30

void render_state_to_window(struct gameState *state, struct window window, struct grid render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

suseconds_t usec(struct timeval *time) {
    return time->tv_sec*1000000 + time->tv_usec;
}

int ceil_f(float f) {
    return ((int)f)+1;
}

int main() {    
    struct window window = window_create();
    struct grid render_grid = render_grid_create(window.rows,window.cols);
    struct gameState state = game_init();
    struct timeval timeout = {.tv_sec = 0, .tv_usec = 5000};

    struct timeval start_compute, end_compute, end_tick;
    suseconds_t diff;

    window_init();
    atexit(window_shutdown);
    while (!state.stop) {
        gettimeofday(&start_compute, NULL);
        render_state_to_window(&state,window,render_grid);
        process_key(&state, window_read_char(timeout));
        gettimeofday(&end_compute, NULL);
        diff = usec(&end_compute) - usec(&start_compute);
        usleep(US_PER_TICK - diff);
        gettimeofday(&end_tick, NULL);
        log_info("fps %d",ceil_f(1000000.0f / (usec(&end_tick) - usec(&start_compute))));
    }

    window_free(window);
    grid_free(render_grid);

    return 0;
}