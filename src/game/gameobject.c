#include <stdlib.h>
#include <stdio.h>

#include "gameobject.h"
#include "../shared/core.h"

game_object* new_collidable(collidables_buf *collidables) {
    if (!(collidables->length < COLLIDABLES_CAPACITY)) {
        die("new_collidable: too many collidables");
    }
    return &collidables->buffer[collidables->length++];
}

struct collidableIterState {
    size_t idx;
    collidables_buf *collidables;
    game_object* target;
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
    while (&state->collidables->buffer[state->idx] == state->target) {
        state->idx++;
    }
    return object_collision_area(&state->collidables->buffer[state->idx++],(ipoint){});
}

int does_object_overlap(game_object *target, ipoint object_offset, collidables_buf *collidables) {
    struct collidableIterState s = {.idx = 0, .collidables = collidables, .target = target};
    collision_area_iter iter = {.state = &s, .next = &iter_next_collision_area, .more = &iter_is_in_range};
    collision_area player_ca = object_collision_area(target, object_offset);
    return collision_check_areas(&player_ca, &iter);
}