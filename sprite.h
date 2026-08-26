#pragma once

#include "point.h"

struct sprite {
    char* design;
    struct point offset;
};

struct sprite sprite_create_from_file(char *filename);
void sprite_free(struct sprite sprite);