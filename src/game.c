#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "log.h"
#include "sys.h"
#include "fps.h"
#include "collision.h"

#define MAX_SPEED 15

struct gameObjectIterState {
    struct gameObjects *objects;
    int idx;
};

int game_objects_is_in_range(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    return state->idx < state->objects->length;
}

struct collisionBox object_collision_box(struct gameObject *object) {
    return (struct collisionBox){.offsets = object->collision_area, .position = to_ipoint(object->position)};
}

struct collisionBox game_objects_next_collision_box(void *_state) {
    struct gameObjectIterState *state = (struct gameObjectIterState*)_state;
    struct gameObject object = state->objects->objects[state->idx++];
    return object_collision_box(&object);
}

int does_object_overlap(struct gameObject *object, struct gameObjects *collidables) {
    struct gameObjectIterState s = {.idx = 0, .objects = collidables};
    struct collisionBoxIter iter = {.state = &s, .next = &game_objects_next_collision_box, .more = &game_objects_is_in_range};
    struct collisionBox player_ca = object_collision_box(object);
    return collision_check_areas(&player_ca, &iter);
}

void update_state(struct gameState *state, struct optional_char c) {
    state->fps = fps_iterate_counters(&state->tick_start_mus, &state->tick_end_mus);

    struct gameObject new_player = state->player; // TODO - refactor this unnecessary copy.
    new_player.velocity = clamp(fpoint_add(new_player.velocity,new_player.acceleration),MAX_SPEED);
    new_player.position = fpoint_add(new_player.position,new_player.velocity);
    if (!does_object_overlap(&new_player, &state->collidables)) {
        state->player.velocity = new_player.velocity;
        state->player.position = new_player.position;
    } else {
        state->player.acceleration = (struct fpoint){};
        state->player.velocity = (struct fpoint){};
    }

    switch (c.value) {
        case 'w':
            
            break;
        case 'a':
            state->player.acceleration.x = -2;
            break;
        case 's':
            
            break;
        case 'd':
            state->player.acceleration.x = 2;
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
        default:
            state->player.acceleration.x = -state->player.velocity.x*0.5;
    }
}

struct gameObjects create_game_objects(struct gameObject game_objects[], int game_object_count) {
    struct gameObjects arr = {.objects = malloc(sizeof(struct gameObject)*game_object_count), .length = game_object_count};
    for (int i = 0 ; i < game_object_count; i++) {
        arr.objects[i] = game_objects[i];
    }
    return arr;
}

#define COLLIDABLE_COUNT 4

struct gameState game_init() {
    struct resources resources = allocate_resources();

    struct gameObjectParseResult parsed_player = parse_game_object_file("game_objects/player.txt");
    struct gameObjectParseResult parsed_box = parse_game_object_file("game_objects/box.txt");
    struct gameObjectParseResult parsed_dot = parse_game_object_file("game_objects/dot.txt");
    struct gameObjectParseResult parsed_floor = parse_game_object_file("game_objects/floor.txt");
    
    struct sprite *player_sprite = sprite_load(&resources, SPRITE_PLAYER, sprite_from_game_object_parse_result(&parsed_player));
    struct sprite *box_sprite    = sprite_load(&resources, SPRITE_BOX,    sprite_from_game_object_parse_result(&parsed_box));
    struct sprite *dot_sprite    = sprite_load(&resources, SPRITE_DOT,    sprite_from_game_object_parse_result(&parsed_dot));
    struct sprite *floor_sprite  = sprite_load(&resources, SPRITE_FLOOR,  sprite_from_game_object_parse_result(&parsed_floor));
    
    collisionArea *player_collision_area = collision_area_load(&resources, COLLISION_AREA_PLAYER, collision_area_from_game_object_parse_result(&parsed_player));
    collisionArea *box_collision_area    = collision_area_load(&resources, COLLISION_AREA_BOX,    collision_area_from_game_object_parse_result(&parsed_box));
    collisionArea *dot_collision_area    = collision_area_load(&resources, COLLISION_AREA_DOT,    collision_area_from_game_object_parse_result(&parsed_dot));
    collisionArea *floor_collision_area  = collision_area_load(&resources, COLLISION_AREA_FLOOR,  collision_area_from_game_object_parse_result(&parsed_floor));
    
    free(parsed_player.collision_area_design);
    free(parsed_box.collision_area_design);
    free(parsed_dot.collision_area_design);
    free(parsed_floor.collision_area_design);
    
    struct gameObject collidables[COLLIDABLE_COUNT] = {
        { .position = {.x = 10,  .y = 5},  .sprite = box_sprite,   .collision_area = box_collision_area   },
        { .position = {.x = 20,  .y = 5},  .sprite = box_sprite,   .collision_area = box_collision_area   },
        { .position = {.x = -10, .y = 5},  .sprite = dot_sprite,   .collision_area = dot_collision_area   },
        { .position = {.x = -50, .y = 10}, .sprite = floor_sprite, .collision_area = floor_collision_area },
    };
    struct gameState state = {
        .stop = 0,
        .tick_start_mus = 0,
        .tick_end_mus = 0,
        .resources = resources,
        .player = { 
            .position = {.x = 0, .y = -10}, 
            .velocity = {.x = 0, .y = 0}, 
            .acceleration = {.x = 0, .y = 0.1},
            .sprite = player_sprite, 
            .collision_area = player_collision_area 
        },
        .collidables = create_game_objects(collidables,COLLIDABLE_COUNT),
    };
    return state;
}

void game_objects_free(struct gameObjects *game_objects) {
    free(game_objects->objects);
}

void game_shutdown(struct gameState* state) {
    game_resources_free(&state->resources);
    game_objects_free(&state->collidables);
}