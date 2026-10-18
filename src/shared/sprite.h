#pragma once

#include "point.h"
#include "design.h"
#include "color.h"

typedef struct sprite {
    design design;
    ipoint offset;
    color *color;
} sprite;

#define SPRITES_CAPACITY 16

typedef struct sprites_buf {
    sprite buffer[SPRITES_CAPACITY];
    size_t length;
} sprites_buf;