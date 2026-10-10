#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "log.h"
#include "sys.h"
#include "fps.h"
#include "collision.h"
#include "gameobject_load.h"

#define MAX_SPEED 15

enum Direction {
    DIRECTION_X,
    DIRECTION_Y
};

float new_velocity_component(game_object *game_object, float velocity_component, enum Direction direction, collidables_buf *collidables) {
    fpoint velocity = {
        .x = (direction == DIRECTION_X) ? velocity_component : 0,
        .y = (direction == DIRECTION_Y) ? velocity_component : 0
    };
    ipoint offset = {.x = ceil_f(velocity.x), .y = ceil_f(velocity.y)};
    if (!does_object_overlap(game_object, offset, collidables)) {
        return velocity_component;
    }
    return 0;
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

void update_state(game_state *state, optional_char c) {
    handle_quit(state,c);
    handle_object_physics(&state->player,&state->collidables,c);
    state->fps = fps_iterate_counters(&state->tick_start_mus, &state->tick_end_mus);
}

game_state game_init(resources *resources) {
    game_object_resources player_resources = load_game_object(resources,"game_objects/player.txt");
    game_object_resources box_resources = load_game_object(resources,"game_objects/box.txt");
    game_object_resources dot_resources = load_game_object(resources,"game_objects/dot.txt");
    game_object_resources floor_resources = load_game_object(resources,"game_objects/floor.txt");
    
    game_state state = {
        .stop = 0,
        .tick_start_mus = 0,
        .tick_end_mus = 0,
        .resources = resources,
        .player = { 
            .position = {.x = 0, .y = -5}, 
            .velocity = {.x = 0, .y = 0}, 
            .sprite = player_resources.sprite, 
            .collision_offset = player_resources.collision_offset 
        },
        .collidables = {
            .buffer = {
                { .position = {.x = 10,  .y = 6},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
                { .position = {.x = 20,  .y = 6},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
                { .position = {.x = -10, .y = 6},  .sprite = dot_resources.sprite,   .collision_offset = dot_resources.collision_offset   },
                { .position = {.x = -50, .y = 10}, .sprite = floor_resources.sprite, .collision_offset = floor_resources.collision_offset },
            },
            .length = 4
        },
    };
    return state;
}