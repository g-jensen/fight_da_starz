#include <stdlib.h>
#include <stdio.h>

#include "gameobject.h"
#include "core.h"

int iter_is_in_range(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    return state->idx < state->objects->length;
}

struct collisionArea object_collision_box(struct gameObject *object) {
    return (struct collisionArea){.offsets = object->collision_offset, .position = to_ipoint(object->position)};
}

struct collisionArea iter_next_collision_box(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    struct gameObject object = state->objects->objects[state->idx++];
    return object_collision_box(&object);
}

int does_object_overlap(struct gameObject *object, struct gameObjects *collidables) {
    struct gameObjectIterState s = {.idx = 0, .objects = collidables};
    struct collisionBoxIter iter = {.state = &s, .next = &iter_next_collision_box, .more = &iter_is_in_range};
    struct collisionArea player_ca = object_collision_box(object);
    return collision_check_areas(&player_ca, &iter);
}