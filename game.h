#pragma once

#include "point.h"
#include "core.h"

struct gameState {
    int stop;
    int counter;
    struct point player_position;
    struct point box_position;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();