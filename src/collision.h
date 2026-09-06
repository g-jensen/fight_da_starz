#pragma once

#include "iterator.h"
#include "point.h"
#include "gameobject.h"

struct collisionBox {
    struct ipoint position;
    struct pointArray *offsets;
};

iterator_define(collisionBoxIter, struct collisionBox)

int collision_check_point(struct ipoint p, struct collisionBox *collision_area);
int collision_check_area(struct collisionBox *ca_0, struct collisionBox *ca_1);
int collision_check_areas(struct collisionBox *ca_0, struct collisionBoxIter *cas);

int is_point_in_game_object(struct ipoint ipoint, struct gameObject *game_object);
int are_game_objects_overlapping(struct gameObject *go_0, struct gameObject *go_1);
int is_object_overlapping(struct gameObject *target, struct gameObjects *objects);