#pragma once

#include "point.h"
#include "sprite.h"
#include "collision.h"

typedef struct game_object {
    fpoint position;
    fpoint velocity;
    fpoint acceleration;
    sprite *sprite;
    collision_offset collision_offset;
} game_object;

#define COLLIDABLES_CAPACITY 256

typedef struct collidables_buf {
    game_object buffer[COLLIDABLES_CAPACITY];
    int length;
} collidables_buf;

int does_object_overlap(game_object *object, ipoint object_offset, collidables_buf *collidables);