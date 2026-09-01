#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"
#include "pointarray.h"
#include "gameobject.h"
#include "resources.h"

struct gameState {
    int stop;
    struct resources resources;
    struct gameObject player;
    struct gameObjects collidables; // TODO - gameObjects having a collisionArea, but not all gameObjects being 'collidables' feels weird here.
    long long tick_start_mus;
    long long tick_end_mus;
    int fps;
};

void update_state(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);
void game_objects_free(struct gameObjects *game_objects);