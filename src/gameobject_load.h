#pragma once

#include "gameobject.h"
#include "resources.h"
#include "sprite.h"
#include "collision.h"
#include "design.h"
#include "color.h"

typedef struct game_object_file_result {
    sprite *sprite;
    collision_offset collision_offset;
} game_object_file_result;

game_object_file_result load_game_object_file(resources *resources, char* filepath);