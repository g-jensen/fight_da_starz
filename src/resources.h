#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"

typedef struct resources {
    designs_buf designs_buf;
    sprites_buf sprites_buf;
    collision_offsets_buf collision_offsets_buf;
} resources;

typedef struct game_object_file_resource {
    sprite *sprite;
    collision_offset collision_offset;
} game_object_file_resource;

typedef struct resources_ref {
    game_object_file_resource player;
    game_object_file_resource box;
    game_object_file_resource dot;
    game_object_file_resource floor;
} resources_ref;

sprite* sprite_new(resources *resources);
resources_ref resources_load(resources *resources);