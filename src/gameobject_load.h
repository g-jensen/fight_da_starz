#pragma once

#include "gameobject.h"
#include "resources.h"
#include "sprite.h"
#include "collision.h"
#include "design.h"

struct gameObjectParseResult {
    struct ipoint offset;
    struct design sprite_design;
    struct collision_offset collision_offset;
};

struct gameObjectParseResult parse_game_object_file(struct designs_buf *designs_buf, struct collision_offsets_buf *collision_offsets_buf, char *filepath);

struct gameObjectResources {
    struct sprite *sprite;
    struct collision_offset collision_offset;
};

struct gameObjectResources load_game_object(resources *resources, char* filepath);