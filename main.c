#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"
#include "log.h"

#include <sys/time.h>
#include <unistd.h>

#define MUS_PER_TICK MS_PER_TICK * 1000
#define MS_PER_TICK 30

void render_state_to_window(struct gameState *state, struct window window, struct grid render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

int main() {    
    struct window window = window_create();
    struct grid render_grid = render_grid_create(window.rows,window.cols);
    struct gameState state = game_init();
    struct timeval timeout = {.tv_sec = 0, .tv_usec = 5000};

    struct timeval start_compute, end_compute;

    window_init();
    atexit(window_shutdown);
    while (!state.stop) {
        gettimeofday(&start_compute, NULL);
        render_state_to_window(&state,window,render_grid);
        process_key(&state, window_read_char(timeout));
        gettimeofday(&end_compute, NULL);
        usleep(MUS_PER_TICK - (mus(&end_compute) - mus(&start_compute)));
    }

    window_free(window);
    grid_free(render_grid);

    return 0;
}