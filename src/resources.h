#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"

struct resources {
    struct designs_buf designs_buf;
    struct sprites_buf sprites_buf;
    collisionOffsets collision_offsets;
};

int resources_init(struct resources *resources);
void game_resources_free(struct resources *resources);
struct sprite* sprite_load(struct resources *resources, struct sprite sprite);
collisionOffset* collision_offset_load(struct resources *resources, collisionOffset collision_area);