#pragma once

#include "iterator.h"
#include "point.h"
#include "pointarray.h"

#define MAX_COLLISION_OFFSET_SIZE 1024
#define MAX_COLLISION_OFFSETS_COUNT 64
#define MAX_COLLISION_OFFSETS_BUFFER MAX_COLLISION_OFFSET_SIZE*MAX_COLLISION_OFFSETS_COUNT

struct collision_offsets_buf {
    struct ipoint buffer[MAX_COLLISION_OFFSETS_BUFFER];
    int length;
};

struct collision_offset {
    struct ipoint *points;
    int length;
};

struct collisionArea {
    struct ipoint position;
    struct collision_offset offsets;
};

iterator_define(collisionAreaIter, struct collisionArea)

int collision_check_point(struct ipoint p, struct collisionArea *collision_area);
int collision_check_area(struct collisionArea *ca_0, struct collisionArea *ca_1);
int collision_check_areas(struct collisionArea *ca_0, struct collisionAreaIter *cas);