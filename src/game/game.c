#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "../shared/sys.h"
#include "fps.h"
#include "../shared/collision.h"

#define MAX_SPEED 15

enum Direction {
    DIRECTION_X,
    DIRECTION_Y
};

float new_velocity_component(game_object *game_object, float velocity_component, enum Direction direction, collidables_buf *collidables) {
    if (velocity_component == 0) return 0;

    int max_offset = (int)velocity_component + sgn_f(velocity_component);
    ipoint offset = {.x = 0, .y = 0};
    int sgn = sgn_f(velocity_component);
    int *nonzero_component = (direction == DIRECTION_X) ? &offset.x : &offset.y;
    while (sgn*(max_offset - *nonzero_component) >= 0) {
        if (does_object_overlap(game_object, offset, collidables)) {
            if (*nonzero_component == 0) {
                return 0;
            }
            return *nonzero_component - sgn;
        }
        (*nonzero_component) += sgn;
    }
    return velocity_component;
}

void simulate_movement(game_object *game_object, collidables_buf *collidables) {
    fpoint velocity = clamp(fpoint_add(game_object->velocity,game_object->acceleration),MAX_SPEED);
    
    game_object->velocity.x = new_velocity_component(game_object,velocity.x,DIRECTION_X,collidables);
    game_object->position.x += game_object->velocity.x;
    
    game_object->velocity.y = new_velocity_component(game_object,velocity.y,DIRECTION_Y,collidables);
    game_object->position.y += game_object->velocity.y;
}

void add_friction(game_object *game_object) {
    game_object->acceleration.x -= game_object->velocity.x*0.3;
}

void add_gravity(game_object *game_object) {
    game_object->acceleration.y += 0.1;
}

void jump(game_object *game_object) {
    game_object->acceleration.y -= 1;
}

int is_grounded(game_object *game_object, collidables_buf *collidables) {
    ipoint offset = {.x = 0, .y = 1};
    return does_object_overlap(game_object, offset, collidables);
}

void push(game_object *game_object, float force) {
    game_object->acceleration.x += force;
}

void add_user_movement(game_object *game_object, optional_char c, int can_jump) {
    if (!c.some) return;
    switch (c.value) {
        case 'w':
            if (can_jump) {
                jump(game_object);
            }
            break;
        case ' ':
            if (can_jump) {
                jump(game_object);
            }
            break;
        case 'a':
            push(game_object, -2);
            break;
        case 'd':
            push(game_object, 2);
            break;
    }
}

void handle_object_physics(game_object *game_object, collidables_buf *collidables, optional_char c) {
    game_object->acceleration = (fpoint){.x=0,.y=0};
    add_gravity(game_object);
    add_friction(game_object);
    add_user_movement(game_object, c, is_grounded(game_object, collidables));
    simulate_movement(game_object, collidables);
}

void handle_quit(game_state *state, optional_char c) {
    if (!c.some) return;
    switch (c.value) {
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

void game_update(game_state *state, optional_char c) {
    handle_quit(state,c);
    handle_object_physics(state->player,&state->collidables,c);
    state->fps = fps_iterate_counters(&state->tick_start_mus, &state->tick_end_mus);
}

void game_init(game_state *state, resources_ref *resources_ref) {
    *state = (game_state){
        .stop = 0,
        .tick_start_mus = 0,
        .tick_end_mus = 0,
    };

    state->player = new_collidable(&state->collidables);
    *state->player = (game_object){
        .position = {.x = 0, .y = -5}, 
        .velocity = {.x = 0, .y = 0}, 
        .sprite = resources_ref->player.sprite, 
        .collision_offset = resources_ref->player.collision_offset 
    };

    *new_collidable(&state->collidables) = (game_object){
        .position = {.x = 10,  .y = 6},  .sprite = resources_ref->box.sprite,   .collision_offset = resources_ref->box.collision_offset
    };
    *new_collidable(&state->collidables) = (game_object){
        .position = {.x = 20,  .y = 6},  .sprite = resources_ref->box.sprite,   .collision_offset = resources_ref->box.collision_offset
    };
    *new_collidable(&state->collidables) = (game_object){
        .position = {.x = -10, .y = 6},  .sprite = resources_ref->dot.sprite,   .collision_offset = resources_ref->dot.collision_offset
    };
    *new_collidable(&state->collidables) = (game_object){
        .position = {.x = -50, .y = 10}, .sprite = resources_ref->floor.sprite, .collision_offset = resources_ref->floor.collision_offset
    };
}