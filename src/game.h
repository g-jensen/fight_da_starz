#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"
#include "pointarray.h"

struct gameObject {
    struct sprite sprite;
    struct point position;
    struct pointArray collision_area;
};

struct gameObjectArray {
    struct gameObject *game_objects;
    int length;
};

struct gameState {
    int stop;
    struct gameObject player;
    struct gameObjectArray collidables;
    int fps;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);
void game_object_free(struct gameObject gameObject);

void game_object_array_free(struct gameObjectArray game_object_array);