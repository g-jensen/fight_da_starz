#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"
#include "pointarray.h"
#include "gameobject.h"

struct gameResources {
    struct sprites sprites;
    collisionAreas collision_areas;
};

struct gameState {
    int stop;
    struct gameResources resources;
    struct gameObject player;
    struct gameObjects collidables; // TODO - gameObjects having a collisionArea, but not all gameObjects being 'collidables' feels weird here.
    int fps;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);
void game_objects_free(struct gameObjects *game_objects);
void game_resources_free(struct gameResources *game_resources);