#include <stdlib.h>
#include <stdio.h>

#include "gameobject.h"
#include "core.h"

struct collidableIterState {
    int idx;
    collidables_buf *collidables;
};

int iter_is_in_range(void *_state) {
    struct collidableIterState *state = (struct collidableIterState*)_state;
    return state->idx < state->collidables->length;
}

collision_area object_collision_area(game_object *object, ipoint object_offset) {
    return (collision_area){.offsets = object->collision_offset, .position = ipoint_add(to_ipoint(object->position),object_offset)};
}

collision_area iter_next_collision_area(void *_state) {
    struct collidableIterState *state = (struct collidableIterState*)_state;
    game_object object = state->collidables->buffer[state->idx++];
    return object_collision_area(&object,(ipoint){});
}

int does_object_overlap(game_object *object, ipoint object_offset, collidables_buf *collidables) {
    struct collidableIterState s = {.idx = 0, .collidables = collidables};
    collision_area_iter iter = {.state = &s, .next = &iter_next_collision_area, .more = &iter_is_in_range};
    collision_area player_ca = object_collision_area(object, object_offset);
    return collision_check_areas(&player_ca, &iter);
}