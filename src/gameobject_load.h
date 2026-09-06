#pragma once

#include "gameobject.h"
#include "resources.h"

struct gameObjectResources {
    struct sprite *sprite;
    collisionOffset *collision_offset;
};

struct gameObjectResources load_game_object(struct resources *resources, char* filepath);