#include <sys/time.h>

#include "game.h"
#include "log.h"

struct timeval start_tick = {}, end_tick = {};

void process_key(struct gameState *state, struct optional_char c) {
    gettimeofday(&end_tick, NULL);
    state->fps = ceil_f(1000000.0f / (mus(&end_tick) - mus(&start_tick)));
    gettimeofday(&start_tick, NULL);
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
        .stop = 0, 
        .player_position = {.x = 0, .y = 0},
        .player_sprite = sprite_create_from_file("sprites/player.txt"),
        .box_position = {.x = 0, .y = 5},
        .box_sprite = sprite_create_from_file("sprites/box.txt"),
    };

    return state;
}

void game_shutdown(struct gameState* state) {
    sprite_free(state->player_sprite);
    sprite_free(state->box_sprite);
}