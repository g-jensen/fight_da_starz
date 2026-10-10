#pragma once

#include "iterator.h"
#include "point.h"

#define MAX_COLLISION_OFFSET_SIZE 1024
#define MAX_COLLISION_OFFSETS_COUNT 64
#define MAX_COLLISION_OFFSETS_BUFFER MAX_COLLISION_OFFSET_SIZE*MAX_COLLISION_OFFSETS_COUNT

typedef struct collision_offsets_buf {
    ipoint buffer[MAX_COLLISION_OFFSETS_BUFFER];
    int length;
} collision_offsets_buf;

typedef struct collision_offset {
    ipoint *points;
    int length;
} collision_offset;

typedef struct collision_area {
    ipoint position;
    collision_offset offsets;
} collision_area;

iterator_define(collision_area_iter, collision_area)

int collision_check_point(ipoint p, collision_area *collision_area);
int collision_check_area(collision_area *ca_0, collision_area *ca_1);
int collision_check_areas(collision_area *ca_0, collision_area_iter *cas);