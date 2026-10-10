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