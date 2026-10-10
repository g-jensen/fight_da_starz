#pragma once

#include "point.h"
#include "sprite.h"
#include "collision.h"

struct gameObject {
    struct fpoint position;
    struct fpoint velocity;
    struct fpoint acceleration;
    struct sprite *sprite;
    struct collision_offset collision_offset;
};

#define COLLIDABLES_CAPACITY 256

struct collidables_buf {
    struct gameObject buffer[COLLIDABLES_CAPACITY];
    int length;
};

int does_object_overlap(struct gameObject *object, struct ipoint object_offset, struct collidables_buf *collidables);