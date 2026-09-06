#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "log.h"
#include "sys.h"
#include "fps.h"
#include "collision.h"

#define MAX_SPEED 15

void update_state(struct gameState *state, struct optional_char c) {
    state->fps = fps_iterate_counters(&state->tick_start_mus, &state->tick_end_mus);

    struct gameObject new_player = state->player; // TODO - refactor this unnecessary copy.
    new_player.velocity = clamp(fpoint_add(new_player.velocity,new_player.acceleration),MAX_SPEED);
    new_player.position = fpoint_add(new_player.position,new_player.velocity);
    if (!does_object_overlap(&new_player, &state->collidables)) {
        state->player = new_player;
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
    memcpy(arr.objects,game_objects,sizeof(struct gameObject)*game_object_count);
    return arr;
}

#define COLLIDABLE_COUNT 4

struct gameObjectResources {
    struct sprite *sprite;
    collisionOffset *collision_offset;
};

struct gameObjectResources load_game_object(struct resources *resources, char* filepath) {
    struct gameObjectParseResult parsed = parse_game_object_file(filepath);
    struct sprite *sprite = sprite_load(resources, sprite_from_parsed_game_object(&parsed));
    collisionOffset *collision_offset = collision_offset_load(resources, collision_offset_from_parsed_game_object(&parsed));
    free(parsed.collision_area_design); // should be: game_object_parse_result_free(&parsed);
    return (struct gameObjectResources){.sprite = sprite, .collision_offset = collision_offset};
}

struct gameState game_init() {
    struct resources resources = allocate_resources();

    struct gameObjectResources player_resources = load_game_object(&resources,"game_objects/player.txt");
    struct gameObjectResources box_resources = load_game_object(&resources,"game_objects/box.txt");
    struct gameObjectResources dot_resources = load_game_object(&resources,"game_objects/dot.txt");
    struct gameObjectResources floor_resources = load_game_object(&resources,"game_objects/floor.txt");
    
    struct gameObject collidables[COLLIDABLE_COUNT] = {
        { .position = {.x = 10,  .y = 5},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
        { .position = {.x = 20,  .y = 5},  .sprite = box_resources.sprite,   .collision_offset = box_resources.collision_offset   },
        { .position = {.x = -10, .y = 5},  .sprite = dot_resources.sprite,   .collision_offset = dot_resources.collision_offset   },
        { .position = {.x = -50, .y = 10}, .sprite = floor_resources.sprite, .collision_offset = floor_resources.collision_offset },
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
            .sprite = player_resources.sprite, 
            .collision_offset = player_resources.collision_offset 
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