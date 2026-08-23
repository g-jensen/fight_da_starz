#include "game.h"
#include "window.h"

void process_key(struct gameState *state) {
    struct optional_char c = window_read_key();
    if (!c.some) return;
    switch (c.value) {
        case 'w':
            state->player_position.y--;
            break;
        case 'a':
            state->player_position.x--;
            break;
        case 's':
            state->player_position.y++;
            break;
        case 'd':
            state->player_position.x++;
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

struct gameState game_init() {
    struct gameState state = {
        .counter = 1, 
        .stop = 0, 
        .player_position = {.x = 0, .y = 0},
        .box_position = {.x = 0, .y = 5} 
    };
    
    return state;
}