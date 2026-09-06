#include <stdlib.h>

#include "resources.h"
#include "core.h"

// eventually define growing array or base the size off of number of files in game_objects/ like allocate_resources(resource_counts(path))
#define MAX_SPRITE_COUNT 8
#define MAX_COLLISION_OFFSET_COUNT 8

struct sprite* sprite_get(struct resources *resources, int sprite_index) {
    return &resources->sprites.items[sprite_index];
}

int sprite_count = 0;

struct sprite* sprite_load(struct resources *resources, struct sprite sprite) {
    if (!(sprite_count < resources->sprites.length)) {
        die("sprite_load: too many sprites");
    }
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
    if (!(collision_offset_count < resources->collision_areas.length)) {
        die("collision_offset_load: too many collision offsets");
    }
    resources->collision_areas.items[collision_offset_count] = collision_area;
    collisionOffset *ptr = collision_offset_get(resources,collision_offset_count);
    collision_offset_count++;
    return ptr;
}

struct resources allocate_resources() {
    struct resources resources = {
        .sprites = {.items = malloc(sizeof(struct sprite)*MAX_SPRITE_COUNT), .length = MAX_SPRITE_COUNT},
        .collision_areas = {.items = malloc(sizeof(collisionOffset)*MAX_COLLISION_OFFSET_COUNT), .length = MAX_COLLISION_OFFSET_COUNT},
    };
    return resources;
}

void game_resources_free(struct resources *game_resources) {
    sprites_free(&game_resources->sprites);
    point_arrays_free(&game_resources->collision_areas);
}