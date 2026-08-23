#pragma once

#include "point.h"
#include "grid.h"
#include "game.h"

#define DEFAULT_CHAR ' '

void render_state_into_grid(struct gameState *state, struct grid grid);