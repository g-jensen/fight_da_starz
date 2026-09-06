#include <stdlib.h>

#include "resources.h"

struct sprite* sprite_get(struct resources *resources, enum spriteIndex sprite_index) {
    return &resources->sprites.items[sprite_index];
}

struct sprite* sprite_load(struct resources *resources, enum spriteIndex sprite_index, struct sprite sprite) {
    resources->sprites.items[sprite_index] = sprite;
    return sprite_get(resources,sprite_index);
}

collisionOffset* collision_offset_get(struct resources *resources, enum collisionOffsetIndex collision_offset_index) {
    return &resources->collision_areas.items[collision_offset_index];
}

collisionOffset* collision_offset_load(struct resources *resources, enum collisionOffsetIndex collision_offset_index, collisionOffset collision_area) {
    resources->collision_areas.items[collision_offset_index] = collision_area;
    return collision_offset_get(resources,collision_offset_index);
}


struct resources allocate_resources() {
    struct resources resources = {
        .sprites = {.items = malloc(sizeof(struct sprite)*SPRITE_COUNT), .length = SPRITE_COUNT},
        .collision_areas = {.items = malloc(sizeof(collisionOffset)*COLLISION_OFFSET_COUNT), .length = COLLISION_OFFSET_COUNT},
    };
    return resources;
}

void game_resources_free(struct resources *game_resources) {
    sprites_free(&game_resources->sprites);
    point_arrays_free(&game_resources->collision_areas);
}