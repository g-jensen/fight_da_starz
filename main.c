#include <stdio.h>
#include <string.h>

#include "core.h"
#include "abuf.h"
#include "raw_mode.h"
#include "window.h"

struct gameState {
    int counter;
};

void set_window_buffer(struct gameState *state, struct abuf *abuf, struct windowConfig *cfg) {
    int y;
    char str[100];
    snprintf(str,100,"I LOVE YOU x%d",state->counter);
    for (y = 0; y < cfg->screenrows; y++) {
        abuf_append(abuf, str, strlen(str));

        window_clear_line(abuf);
        if (y < cfg->screenrows - 1) {
            abuf_append(abuf, "\r\n", 2);
        }
    }
}

void process_key(struct gameState *state, struct abuf *abuf) {
    char c = window_read_key();
    switch (c) {
        case 'g':
            state->counter++;
            break;
        case CTRL_KEY('c'):
            abuf_free(abuf);
            window_clear_screen();
            exit(0);
            break;
    }
}

int main() {
    enable_raw_mode();
    
    struct windowConfig cfg;
    window_init_config(&cfg);

    struct abuf abuf = ABUF_INIT;

    struct gameState state = {.counter = 1};

    while (1) {
        set_window_buffer(&state,&abuf,&cfg);
        window_draw_screen(&abuf, &cfg);
        process_key(&state, &abuf);
    }

    return 0;
}