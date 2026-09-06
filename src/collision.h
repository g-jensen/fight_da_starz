#pragma once

#include "iterator.h"
#include "point.h"
#include "pointarray.h"

typedef struct pointArray collisionOffset;
typedef struct pointArrays collisionOffsets;

struct collisionBox {
    struct ipoint position;
    collisionOffset *offsets;
};

iterator_define(collisionBoxIter, struct collisionBox)

int collision_check_point(struct ipoint p, struct collisionBox *collision_area);
int collision_check_area(struct collisionBox *ca_0, struct collisionBox *ca_1);
int collision_check_areas(struct collisionBox *ca_0, struct collisionBoxIter *cas);