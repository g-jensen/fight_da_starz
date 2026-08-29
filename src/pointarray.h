#pragma once

#include "point.h"

struct pointArray {
    struct point *points;
    int length;
};

struct pointArrays {
    struct pointArray *items;
    int length;
};

void point_array_free(struct pointArray *point_array);
void point_arrays_free(struct pointArrays *point_array);