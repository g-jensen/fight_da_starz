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

enum collisionOffsetIndex {
    COLLISION_OFFSET_PLAYER,
    COLLISION_OFFSET_BOX,
    COLLISION_OFFSET_DOT,
    COLLISION_OFFSET_FLOOR,

    COLLISION_OFFSET_COUNT // keep this at the end
};

struct resources allocate_resources();
void game_resources_free(struct resources *resources);
struct sprite* sprite_get(struct resources *resources, enum spriteIndex sprite_index);
struct sprite* sprite_load(struct resources *resources, enum spriteIndex sprite_index, struct sprite sprite);
collisionOffset* collision_offset_get(struct resources *resources, enum collisionOffsetIndex collision_offset_index);
collisionOffset* collision_offset_load(struct resources *resources, enum collisionOffsetIndex collision_offset_index, collisionOffset collision_area);