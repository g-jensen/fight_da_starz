#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"

struct resources {
    struct designs_buf designs_buf;
    struct sprites_buf sprites_buf;
    struct collision_offsets_buf collision_offsets_buf;
};

int resources_init(struct resources *resources);
struct sprite* sprite_load(struct resources *resources, struct sprite sprite);
