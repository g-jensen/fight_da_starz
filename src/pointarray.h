#pragma once

#include "point.h"

struct pointArray {
    struct ipoint *points;
    int length;
    int capacity;
};

struct pointArrays {
    struct pointArray *items;
    int length;
    int capacity;
};

void point_array_free(struct pointArray *point_array);
void point_arrays_free(struct pointArrays *point_array);