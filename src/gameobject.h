#pragma once

#include "point.h"
#include "sprite.h"
#include "collision.h"

struct gameObjectParseResult {
    struct ipoint offset;
    char* sprite_design;
    char* collision_area_design;
};

struct gameObjectParseResult parse_game_object_file(char *filename);
void game_object_parse_result_free(struct gameObjectParseResult *parse_result);
struct sprite sprite_from_parsed_game_object(struct gameObjectParseResult *parse_result);
collisionOffset collision_offset_from_parsed_game_object(struct gameObjectParseResult *parse_result);

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

struct gameObjectIterState {
    struct gameObjects *objects;
    int idx;
};

int does_object_overlap(struct gameObject *object, struct gameObjects *collidables);