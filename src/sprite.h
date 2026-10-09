#pragma once

#include "point.h"
#include "design.h"

struct sprite {
    struct design design;
    struct ipoint offset;
};

#define SPRITES_CAPACITY 16

struct sprites_buf {
    struct sprite buffer[SPRITES_CAPACITY];
    int length;
};