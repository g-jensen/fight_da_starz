#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"
#include "pointarray.h"
#include "gameobject.h"
#include "resources.h"

typedef struct game_state {
    int stop;
    resources *resources;
    struct gameObject player;
    struct collidables_buf collidables; // TODO - gameObjects having a collisionArea, but not all gameObjects being 'collidables' feels weird here.
    long long tick_start_mus;
    long long tick_end_mus;
    int fps;
} game_state;

void update_state(game_state *state, struct optional_char c);
game_state game_init(resources *resources);
