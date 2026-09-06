#pragma once

#include "point.h"
#include "sprite.h"
#include "collision.h"

struct gameObjectParseResult {
    struct ipoint offset;
    char* sprite_design;
    char* collision_area_design;
};

struct gameObject {
    struct fpoint position;
    struct fpoint velocity;
    struct fpoint acceleration;
    struct sprite *sprite;
    collisionOffset *collision_offset;
};

struct gameObjects {
    struct gameObject *objects;
    int length;
};

struct gameObjectParseResult parse_game_object_file(char *filename);
struct sprite sprite_from_game_object_parse_result(struct gameObjectParseResult *parse_result);
collisionOffset collision_area_from_game_object_parse_result(struct gameObjectParseResult *parse_result);