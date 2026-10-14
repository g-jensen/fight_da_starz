#pragma once

#include "gameobject.h"
#include "resources.h"
#include "sprite.h"
#include "collision.h"
#include "design.h"
#include "color.h"

typedef struct game_object_parse_result {
    ipoint offset;
    design sprite_design;
    collision_offset collision_offset;
    color color;
} game_object_parse_result;

void parse_game_object_file(game_object_parse_result *parse_result, resources *resources, char *filepath);

typedef struct game_object_resources {
    sprite *sprite;
    collision_offset collision_offset;
} game_object_resources;

game_object_resources load_game_object(resources *resources, char* filepath);