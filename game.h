#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"

struct gameState {
    int stop;
    struct point player_position;
    struct sprite player_sprite;
    struct point box_position;
    struct sprite box_sprite;
    int fps;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);