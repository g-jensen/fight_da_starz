#include <stdlib.h>

#include "resources.h"

struct sprite* sprite_get(struct resources *resources, int sprite_index) {
    return &resources->sprites.items[sprite_index];
}

int sprite_count = 0;

struct sprite* sprite_load(struct resources *resources, struct sprite sprite) {
    resources->sprites.items[sprite_count] = sprite;
    struct sprite *ptr = sprite_get(resources,sprite_count);
    sprite_count++;
    return ptr;
}

collisionOffset* collision_offset_get(struct resources *resources, int collision_offset_index) {
    return &resources->collision_areas.items[collision_offset_index];
}

int collision_offset_count = 0;

collisionOffset* collision_offset_load(struct resources *resources, collisionOffset collision_area) {
    resources->collision_areas.items[collision_offset_count] = collision_area;
    collisionOffset *ptr = collision_offset_get(resources,collision_offset_count);
    collision_offset_count++;
    return ptr;
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