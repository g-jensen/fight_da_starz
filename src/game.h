#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"
#include "pointarray.h"

typedef struct pointArray collisionArea;
typedef struct pointArrays collisionAreas;

struct gameObject {
    struct sprite *sprite;
    struct point position;
    collisionArea *collision_area;
};

struct gameObjects {
    struct gameObject *objects;
    int length;
};

struct gameResources {
    struct sprites sprites;
    collisionAreas collision_areas;
};

struct gameState {
    int stop;
    struct gameResources resources;
    struct gameObject player;
    struct gameObjects collidables;
    int fps;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);
void game_objects_free(struct gameObjects *game_objects);
void game_resources_free(struct gameResources *game_resources);