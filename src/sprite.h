#pragma once

#include "point.h"

struct sprite {
    char* design;
    struct ipoint offset;
};

struct sprites {
    struct sprite *items;
    int length;
};

struct sprite sprite_create_from_file(char *filename);
void sprite_free(struct sprite *sprite);
void sprites_free(struct sprites *sprite);