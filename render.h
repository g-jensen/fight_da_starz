#pragma once

#include "point.h"
#include "grid.h"
#include "game.h"

#define DEFAULT_CHAR ' '

struct sprite {
    char* design;
    struct point offset;
};

struct grid render_grid_create(int rows, int cols);
void render_state_into_grid(struct gameState *state, struct grid grid);