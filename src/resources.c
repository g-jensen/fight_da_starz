#include <stdlib.h>

#include "resources.h"
#include "core.h"

// eventually define growing array or base the size off of number of files in game_objects/ like allocate_resources(resource_counts(path))
#define MAX_SPRITE_COUNT 8
#define MAX_COLLISION_OFFSET_COUNT 8

struct sprite* sprite_get(struct resources *resources, int sprite_index) {
    return &resources->sprites.items[sprite_index];
}

struct sprite* sprite_load(struct resources *resources, struct sprite sprite) {
    if (!(resources->sprites.length < resources->sprites.capacity)) {
        die("sprite_load: too many sprites");
    }
    resources->sprites.items[resources->sprites.length] = sprite;
    struct sprite *ptr = sprite_get(resources,resources->sprites.length);
    resources->sprites.length++;
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

struct resources allocate_resources() {
    struct resources resources = {
        .sprites = {.items = malloc(sizeof(struct sprite)*MAX_SPRITE_COUNT), .length = 0, .capacity = MAX_SPRITE_COUNT},
        .collision_offsets = {.items = malloc(sizeof(collisionOffset)*MAX_COLLISION_OFFSET_COUNT), .length = 0, .capacity = MAX_COLLISION_OFFSET_COUNT},
    };
    return resources;
}

void game_resources_free(struct resources *game_resources) {
    sprites_free(&game_resources->sprites);
    point_arrays_free(&game_resources->collision_offsets);
}