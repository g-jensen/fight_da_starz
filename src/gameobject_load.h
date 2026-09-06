#pragma once

#include "gameobject.h"
#include "resources.h"
#include "sprite.h"
#include "collision.h"

struct gameObjectParseResult {
    struct ipoint offset;
    char* sprite_design;
    char* collision_area_design;
};

struct gameObjectParseResult parse_game_object_file(char *filepath);

struct gameObjectResources {
    struct sprite *sprite;
    collisionOffset *collision_offset;
};

struct gameObjectResources load_game_object(struct resources *resources, char* filepath);