#include <stdlib.h>
#include <stdio.h>

#include "gameobject.h"
#include "core.h"

int iter_is_in_range(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    return state->idx < state->objects->length;
}

struct collisionArea object_collision_area(struct gameObject *object, struct ipoint object_offset) {
    return (struct collisionArea){.offsets = object->collision_offset, .position = ipoint_add(to_ipoint(object->position),object_offset)};
}

struct collisionArea iter_next_collision_area(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    struct gameObject object = state->objects->items[state->idx++];
    return object_collision_area(&object,(struct ipoint){});
}

int does_object_overlap(struct gameObject *object, struct ipoint object_offset, struct gameObjects *collidables) {
    struct gameObjectIterState s = {.idx = 0, .objects = collidables};
    struct collisionAreaIter iter = {.state = &s, .next = &iter_next_collision_area, .more = &iter_is_in_range};
    struct collisionArea player_ca = object_collision_area(object, object_offset);
    return collision_check_areas(&player_ca, &iter);
}