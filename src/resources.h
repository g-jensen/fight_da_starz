#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"

typedef struct resources {
    struct designs_buf designs_buf;
    struct sprites_buf sprites_buf;
    struct collision_offsets_buf collision_offsets_buf;
} resources;

int resources_init(resources *resources);
struct sprite* sprite_load(resources *resources, struct sprite sprite);
