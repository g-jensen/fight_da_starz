#pragma once

#include "gameobject.h"
#include "resources.h"
#include "sprite.h"
#include "collision.h"
#include "design.h"

typedef struct game_object_parse_result {
    ipoint offset;
    design sprite_design;
    collision_offset collision_offset;
} game_object_parse_result;

game_object_parse_result parse_game_object_file(designs_buf *designs_buf, collision_offsets_buf *collision_offsets_buf, char *filepath);

typedef struct game_object_resources {
    sprite *sprite;
    collision_offset collision_offset;
} game_object_resources;

game_object_resources load_game_object(resources *resources, char* filepath);