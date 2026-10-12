#pragma once

#include "point.h"
#include "design.h"

typedef struct sprite {
    design design;
    ipoint offset;
    char color[16];
} sprite;

#define SPRITES_CAPACITY 16

typedef struct sprites_buf {
    sprite buffer[SPRITES_CAPACITY];
    int length;
} sprites_buf;