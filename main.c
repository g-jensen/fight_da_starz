#include "render.h"
#include "grid.h"
#include "window.h"
#include "game.h"
#include "log.h"
#include "keycode.h"
#include "uiohook.h"

void render_state_to_window(struct gameState *state, struct window window, struct grid render_grid) {
    render_state_into_grid(state,render_grid);
    window_draw(window,render_grid);
}

void on_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_KEY_PRESSED:
            log_info("PRESSED: %s",keycode_to_name(event->data.keyboard.keycode));
            break;
        case EVENT_KEY_RELEASED:
            log_info("RELEASED: %s",keycode_to_name(event->data.keyboard.keycode));
            break;
        default:
            break;
    }
}

int main() {    
    struct window window = window_create();
    struct grid render_grid = render_grid_create(window.rows,window.cols);
    struct gameState state = game_init();
    pthread_t uiohook_thread = uiohook_init();
    hook_set_dispatch_proc(&on_event);
    
    window_init();
    atexit(window_shutdown);
    while (!state.stop) {
        render_state_to_window(&state,window,render_grid);
        process_key(&state, window_read_key()); // replace terminal character reading with full-scale key reading? https://github.com/kwhat/libuiohook
    }
    uiohook_shutdown(uiohook_thread);

    window_free(window);
    grid_free(render_grid);

    return 0;
}