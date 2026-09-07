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

void simulate_movement_direction(struct gameObject *game_object, float *direction, struct fpoint offset, struct gameObjects *collidables) {
    if (!does_object_overlap(game_object, (struct ipoint){.x=ceil_f(offset.x),.y=ceil_f(offset.y)}, collidables)) {
        *direction = offset.y == 0 ? offset.x : offset.y; // feels yucky
        game_object->position = fpoint_add(game_object->position,offset);
    } else {
        *direction = 0;
    }
}

void simulate_movement(struct gameObject *game_object, struct gameObjects *collidables) {
    struct fpoint velocity = clamp(fpoint_add(game_object->velocity,game_object->acceleration),MAX_SPEED);
    simulate_movement_direction(game_object, &game_object->velocity.x,(struct fpoint){.x=velocity.x,.y=0},collidables);
    simulate_movement_direction(game_object, &game_object->velocity.y,(struct fpoint){.x=0,.y=velocity.y},collidables);
}

void add_friction(struct gameObject *game_object) {
    game_object->acceleration.x -= game_object->velocity.x*0.3;
}

void add_gravity(struct gameObject *game_object) {
    game_object->acceleration.y += 0.1;
}

void add_user_movement(struct gameObject *game_object, struct optional_char c) {
    if (!c.some) return;
    switch (c.value) {
        case 'w':
            
            break;
        case 'a':
            game_object->acceleration.x -= 2;
            break;
        case 's':
            
            break;
        case 'd':
            game_object->acceleration.x += 2;
            break;
    }
}

void handle_object_physics(struct gameObject *game_object, struct gameObjects *collidables, struct optional_char c) {
    game_object->acceleration = (struct fpoint){.x=0,.y=0};
    add_gravity(game_object);
    add_friction(game_object);
    add_user_movement(game_object,c);
    simulate_movement(game_object,collidables);
}

void handle_quit(struct gameState *state, struct optional_char c) {
    if (!c.some) return;
    switch (c.value) {
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

void update_state(struct gameState *state, struct optional_char c) {
    handle_quit(state,c);
    handle_object_physics(&state->player,&state->collidables,c);
    state->fps = fps_iterate_counters(&state->tick_start_mus, &state->tick_end_mus);
}

struct gameObjects create_game_objects(struct gameObject game_objects[], int game_object_count) {
    struct gameObjects arr = {.items = malloc(sizeof(struct gameObject)*game_object_count), .length = game_object_count};
    memcpy(arr.items,game_objects,sizeof(struct gameObject)*game_object_count);
    return arr;
}

#define COLLIDABLE_COUNT 4

struct gameState game_init() {
    struct resources resources = allocate_resources();

    struct gameObjectResources player_resources = load_game_object(&resources,"game_objects/player.txt");
    struct gameObjectResources box_resources = load_game_object(&resources,"game_objects/box.txt");
    struct gameObjectResources dot_resources = load_game_object(&resources,"game_objects/dot.txt");
    struct gameObjectResources floor_resources = load_game_object(&resources,"game_objects/floor.txt");
    
    struct gameObject collidables[COLLIDABLE_COUNT] = {
        { .position = {.x = 10,  .y = 6},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
        { .position = {.x = 20,  .y = 6},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
        { .position = {.x = -10, .y = 6},  .sprite = dot_resources.sprite,   .collision_offset = dot_resources.collision_offset   },
        { .position = {.x = -50, .y = 10}, .sprite = floor_resources.sprite, .collision_offset = floor_resources.collision_offset },
    };
    struct gameState state = {
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
        .collidables = create_game_objects(collidables,COLLIDABLE_COUNT),
    };
    return state;
}

void game_objects_free(struct gameObjects *game_objects) {
    free(game_objects->items);
}

void game_shutdown(struct gameState* state) {
    game_resources_free(&state->resources);
    game_objects_free(&state->collidables);
}