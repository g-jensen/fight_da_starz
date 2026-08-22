#include "core.h"
#include "abuf.h"
#include "raw_mode.h"
#include "window.h"

struct gameState {
    int counter;
};

void set_buffer(struct gameState *state, struct abuf *ab, struct windowConfig *cfg) {
    int y;
    char str[100];
    snprintf(str,100,"I LOVE YOU x%d",state->counter);
    for (y = 0; y < cfg->screenrows; y++) {
        abuf_append(ab, str, strlen(str));

        window_clear_line(ab);
        if (y < cfg->screenrows - 1) {
            abuf_append(ab, "\r\n", 2);
        }
    }
}

void window_process_key(struct gameState *state, struct abuf *ab) {
    char c = window_read_key();
    switch (c) {
        case 'g':
            state->counter++;
            break;
        case CTRL_KEY('c'):
            abuf_free(ab);
            window_clear_screen();
            exit(0);
            break;
    }
}

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);

    struct abuf ab = ABUF_INIT;

    struct gameState state = {.counter = 1};

    while (1) {
        set_buffer(&state,&ab,&cfg);
        window_draw_screen(&ab, &cfg);
        window_process_key(&state, &ab);
    }

    return 0;
}