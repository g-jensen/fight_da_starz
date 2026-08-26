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
            state->player.position.y--;
            break;
        case 'a':
            state->player.position.x--;
            break;
        case 's':
            state->player.position.y++;
            break;
        case 'd':
            state->player.position.x++;
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

struct gameState game_init() {
    struct gameState state = {
        .stop = 0, 
        .player = {.position = {.x = 0, .y = 0}, .sprite = sprite_create_from_file("sprites/player.txt")},
        .box = {.position = {.x = 0, .y = 5}, .sprite = sprite_create_from_file("sprites/box.txt")},
    };

    return state;
}

void game_shutdown(struct gameState* state) {
    game_object_free(state->player);
    game_object_free(state->box);
}

void game_object_free(struct gameObject gameObject) {
    sprite_free(gameObject.sprite);
}