#pragma once

#include "point.h"
#include "gameobject.h"

int is_point_in_game_object(struct ipoint ipoint, struct gameObject *game_object);
int are_game_objects_overlapping(struct gameObject *go_0, struct gameObject *go_1);
int is_object_overlapping(struct gameObject *target, struct gameObjects *objects);