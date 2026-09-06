#pragma once

#include "sprite.h"
#include "collision.h"

struct resources {
    struct sprites sprites;
    collisionOffsets collision_areas;
};

enum spriteIndex {
    SPRITE_PLAYER,
    SPRITE_BOX,
    SPRITE_DOT,
    SPRITE_FLOOR,

    SPRITE_COUNT // keep this at the end
};

enum collisionAreaIndex {
    COLLISION_AREA_PLAYER,
    COLLISION_AREA_BOX,
    COLLISION_AREA_DOT,
    COLLISION_AREA_FLOOR,

    COLLISION_AREA_COUNT // keep this at the end
};

struct resources allocate_resources();
void game_resources_free(struct resources *resources);
struct sprite* sprite_get(struct resources *resources, enum spriteIndex sprite_index);
struct sprite* sprite_load(struct resources *resources, enum spriteIndex sprite_index, struct sprite sprite);
collisionOffset* collision_area_get(struct resources *resources, enum collisionAreaIndex collision_area_index);
collisionOffset* collision_area_load(struct resources *resources, enum collisionAreaIndex collision_area_index, collisionOffset collision_area);