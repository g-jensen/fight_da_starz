#pragma once

#include "iterator.h"
#include "point.h"
#include "pointarray.h"

typedef struct pointArray collisionOffset;
typedef struct pointArrays collisionOffsets;

struct collisionArea {
    struct ipoint position;
    collisionOffset *offsets;
};

iterator_define(collisionBoxIter, struct collisionArea)

int collision_check_point(struct ipoint p, struct collisionArea *collision_area);
int collision_check_area(struct collisionArea *ca_0, struct collisionArea *ca_1);
int collision_check_areas(struct collisionArea *ca_0, struct collisionBoxIter *cas);