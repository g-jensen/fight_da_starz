#pragma once

#include "sprite.h"
#include "collision.h"

struct resources {
    struct sprites sprites;
    collisionOffsets collision_areas;
};

struct resources allocate_resources();
void game_resources_free(struct resources *resources);
struct sprite* sprite_load(struct resources *resources, struct sprite sprite);
collisionOffset* collision_offset_load(struct resources *resources, collisionOffset collision_area);