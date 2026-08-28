#pragma once

#include "point.h"
#include "core.h"
#include "sprite.h"

struct gameObject {
    struct sprite sprite;
    struct point position;
    struct point *collision_area;
    int collision_area_length;
};

struct gameState {
    int stop;
    struct gameObject player;
    struct gameObject box;
    int fps;
};

void process_key(struct gameState *state, struct optional_char c);
struct gameState game_init();
void game_shutdown(struct gameState* state);
void game_object_free(struct gameObject gameObject);