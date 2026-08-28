#pragma once

#include "point.h"

struct pointArray {
    struct point *points;
    int length;
};

void point_array_free(struct pointArray point_array);