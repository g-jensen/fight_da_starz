#pragma once

#include "point.h"
#include "sprite.h"
#include "collision.h"

struct gameObject {
    struct fpoint position;
    struct fpoint velocity;
    struct fpoint acceleration;
    struct sprite *sprite;
    collisionOffset *collision_offset;
};

struct gameObjects {
    struct gameObject *items;
    int length;
};

struct gameObjectIterState {
    struct gameObjects *objects;
    int idx;
};

int does_object_overlap(struct gameObject *object, struct ipoint object_offset, struct gameObjects *collidables);