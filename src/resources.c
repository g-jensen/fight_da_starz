#include <stdlib.h>

#include "resources.h"

struct sprite* sprite_get(struct resources *resources, enum spriteIndex sprite_index) {
    return &resources->sprites.items[sprite_index];
}

struct sprite* sprite_load(struct resources *resources, enum spriteIndex sprite_index, struct sprite sprite) {
    resources->sprites.items[sprite_index] = sprite;
    return sprite_get(resources,sprite_index);
}

collisionArea* collision_area_get(struct resources *resources, enum collisionAreaIndex collision_area_index) {
    return &resources->collision_areas.items[collision_area_index];
}

collisionArea* collision_area_load(struct resources *resources, enum collisionAreaIndex collision_area_index, collisionArea collision_area) {
    resources->collision_areas.items[collision_area_index] = collision_area;
    return collision_area_get(resources,collision_area_index);
}


struct resources allocate_resources() {
    struct resources resources = {
        .sprites = {.items = malloc(sizeof(struct sprite)*SPRITE_COUNT), .length = SPRITE_COUNT},
        .collision_areas = {.items = malloc(sizeof(collisionArea)*COLLISION_AREA_COUNT), .length = COLLISION_AREA_COUNT},
    };
    return resources;
}

void game_resources_free(struct resources *game_resources) {
    sprites_free(&game_resources->sprites);
    point_arrays_free(&game_resources->collision_areas);
}