#pragma once

#include "point.h"
#include "sprite.h"
#include "pointarray.h"

typedef struct pointArray collisionArea;
typedef struct pointArrays collisionAreas;

struct gameObjectParseResult {
    struct point offset;
    char* sprite_design;
    char* collision_area_design;
};

struct gameObject {
    struct sprite *sprite;
    struct point position;
    collisionArea *collision_area;
};

struct gameObjects {
    struct gameObject *objects;
    int length;
};

struct gameObjectParseResult parse_game_object_file(char *filename);
struct sprite sprite_from_game_object_parse_result(struct gameObjectParseResult *parse_result);
collisionArea collision_area_from_game_object_parse_result(struct gameObjectParseResult *parse_result);