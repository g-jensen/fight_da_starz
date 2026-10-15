#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"
#include "gameobject_file.h"

typedef struct resources {
    designs_buf designs_buf;
    sprites_buf sprites_buf;
    collision_offsets_buf collision_offsets_buf;
} resources;

typedef struct resources_ref {
    game_object_file_result player;
    game_object_file_result box;
    game_object_file_result dot;
    game_object_file_result floor;
} resources_ref;

sprite* sprite_new(resources *resources);
resources_ref resources_load(resources *resources);