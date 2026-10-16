#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"
#include "color.h"

typedef struct color_resources {
    color_param_buf param_buf;
    color_buf color_buf;
} color_resources;

typedef struct resources {
    designs_buf designs_buf;
    color_resources color_resources;
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
color* color_new(resources *resources);
resources_ref resources_load(resources *resources);