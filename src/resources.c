#include <stdlib.h>

#include "resources.h"
#include "core.h"
#include "sys.h"

#define MAX_SPRITE_COUNT 8
#define MAX_COLLISION_OFFSET_COUNT 8

struct sprite* sprite_get(struct resources *resources, int sprite_index) {
    return &resources->sprites_buf.buffer[sprite_index];
}

struct sprite* sprite_load(struct resources *resources, struct sprite sprite) {
    if (!(resources->sprites_buf.length < SPRITES_CAPACITY)) {
        die("sprite_load: too many sprites_buf");
    }
    resources->sprites_buf.buffer[resources->sprites_buf.length] = sprite;
    struct sprite *ptr = sprite_get(resources,resources->sprites_buf.length);
    resources->sprites_buf.length++;
    return ptr;
}

collisionOffset* collision_offset_get(struct resources *resources, int collision_offset_index) {
    return &resources->collision_offsets.items[collision_offset_index];
}

collisionOffset* collision_offset_load(struct resources *resources, collisionOffset collision_area) {
    if (!(resources->collision_offsets.length < resources->collision_offsets.capacity)) {
        die("collision_offset_load: too many collision offsets");
    }
    resources->collision_offsets.items[resources->collision_offsets.length] = collision_area;
    collisionOffset *ptr = collision_offset_get(resources,resources->collision_offsets.length);
    resources->collision_offsets.length++;
    return ptr;
}

int resources_init(struct resources *resources) {
    *resources = (struct resources){
        .designs_buf = {},
        .sprites_buf = {},
        .collision_offsets = {.items = memory_map(sizeof(collisionOffset)*MAX_COLLISION_OFFSET_COUNT), .length = 0, .capacity = MAX_COLLISION_OFFSET_COUNT},
    };
    return 0;
}

void game_resources_free(struct resources *game_resources) {
    point_arrays_free(&game_resources->collision_offsets);
}