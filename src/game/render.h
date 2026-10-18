#pragma once

#include "../shared/point.h"
#include "../shared/color.h"
#include "grid.h"
#include "game.h"

#define DEFAULT_CHAR ' '
extern color DEFAULT_COLOR;

int render_grid_create(grid *grid, int rows, int cols);
void render_state_into_grid(game_state *state, grid *grid); // TODO - change to render_sprites_into_grid. `render` shouldn't know about `game`. maybe include `camera` abstraction.