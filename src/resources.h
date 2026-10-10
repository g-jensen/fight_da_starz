#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"

typedef struct resources {
    designs_buf designs_buf;
    sprites_buf sprites_buf;
    collision_offsets_buf collision_offsets_buf;
} resources;

int resources_init(resources *resources);
sprite* sprite_load(resources *resources, sprite sprite);
