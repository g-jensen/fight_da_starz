#pragma once

#include "point.h"
#include "grid.h"
#include "game.h"

#define DEFAULT_CHAR ' '

void place_char(struct point p, struct grid grid, char c);
struct point render_position(struct point p, struct point rendered_player_position, struct point real_player_position);
void state_to_grid(struct gameState *state, struct grid grid);