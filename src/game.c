#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "log.h"
#include "sys.h"

int is_point_in_game_object(struct point point, struct gameObject *game_object) {
    for(int i = 0; i < game_object->collision_area->length; i++) {
        struct point current_object_point = point_add(game_object->collision_area->points[i], game_object->position);
        if (point_eq(point,current_object_point)) {
            return 1;
        }
    }
    return 0;
}

int are_game_objects_overlapping(struct gameObject *go_0, struct gameObject *go_1) {
    for(int i = 0; i < go_0->collision_area->length; i++) {
        struct point current_player_position = point_add(go_0->collision_area->points[i], go_0->position);
        
        if (is_point_in_game_object(current_player_position,go_1)) {
            return 1;
        }
    }
    return 0;
}

int is_object_overlapping(struct gameObject *target, struct gameObjects *objects) {
    for (int i = 0; i < objects->length; i++) {
        if (are_game_objects_overlapping(target,&objects->objects[i])) {
            return 1;
        }
    }
    return 0;
}

long long start_tick = 0, end_tick = 0;

void process_key(struct gameState *state, struct optional_char c) {
    end_tick = get_time_mus();
    state->fps = ceil_f(1000000.0f / (end_tick - start_tick));
    start_tick = get_time_mus();
    if (!c.some) return;
    struct gameObject new_player = state->player; // TODO - refactor this unnecessary copy.
    switch (c.value) {
        case 'w':
            new_player.position.y--;
            if(!is_object_overlapping(&new_player, &state->collidables)) {
                state->player.position.y--;
            }
            break;
        case 'a':
            new_player.position.x--;
            if(!is_object_overlapping(&new_player, &state->collidables)) {
                state->player.position.x--;
            }
            break;
        case 's':
            new_player.position.y++;
            if(!is_object_overlapping(&new_player, &state->collidables)) {
                state->player.position.y++;
            }
            break;
        case 'd':
            new_player.position.x++;
            if(!is_object_overlapping(&new_player, &state->collidables)) {
                state->player.position.x++;
            }
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

struct gameObjects create_game_objects(struct gameObject game_objects[], int game_object_count) {
    struct gameObjects arr = {.objects = malloc(sizeof(struct gameObject)*game_object_count), .length = game_object_count};
    for (int i = 0 ; i < game_object_count; i++) {
        arr.objects[i] = game_objects[i];
    }
    return arr;
}

enum spriteIndex {
    SPRITE_PLAYER,
    SPRITE_BOX,
    SPRITE_DOT,
};

enum collisionAreaIndex {
    COLLISION_AREA_PLAYER,
    COLLISION_AREA_BOX,
    COLLISION_AREA_DOT,
};

struct sprite* sprite_get(struct gameResources *resources, enum spriteIndex sprite_index) {
    return &resources->sprites.items[sprite_index];
}

struct sprite* sprite_load(struct gameResources *resources, enum spriteIndex sprite_index, struct sprite sprite) {
    resources->sprites.items[sprite_index] = sprite;
    return sprite_get(resources,sprite_index);
}

collisionArea* collision_area_get(struct gameResources *resources, enum collisionAreaIndex collision_area_index) {
    return &resources->collision_areas.items[collision_area_index];
}

collisionArea* collision_area_load(struct gameResources *resources, enum collisionAreaIndex collision_area_index, collisionArea collision_area) {
    resources->collision_areas.items[collision_area_index] = collision_area;
    return collision_area_get(resources,collision_area_index);
}

#define COLLIDABLE_COUNT 3
#define COLLISION_AREA_COUNT 3
#define SPRITE_COUNT 3

struct gameResources allocate_resources() {
    struct gameResources resources = {
        .sprites = {.items = malloc(sizeof(struct sprite)*SPRITE_COUNT), .length = SPRITE_COUNT},
        .collision_areas = {.items = malloc(sizeof(collisionArea)*COLLISION_AREA_COUNT), .length = COLLISION_AREA_COUNT},
    };
    return resources;
}

struct gameState game_init() {
    struct gameResources resources = allocate_resources();

    struct gameObjectParseResult parsed_player = parse_game_object_file("game_objects/player.txt");
    struct gameObjectParseResult parsed_box = parse_game_object_file("game_objects/box.txt");
    struct gameObjectParseResult parsed_dot = parse_game_object_file("game_objects/dot.txt");
    
    struct sprite *player_sprite = sprite_load(&resources, SPRITE_PLAYER, sprite_from_game_object_parse_result(&parsed_player));
    struct sprite *box_sprite    = sprite_load(&resources, SPRITE_BOX,    sprite_from_game_object_parse_result(&parsed_box));
    struct sprite *dot_sprite    = sprite_load(&resources, SPRITE_DOT,    sprite_from_game_object_parse_result(&parsed_dot));
    
    collisionArea *player_collision_area = collision_area_load(&resources, COLLISION_AREA_PLAYER, collision_area_from_game_object_parse_result(&parsed_player));
    collisionArea *box_collision_area    = collision_area_load(&resources, COLLISION_AREA_BOX,    collision_area_from_game_object_parse_result(&parsed_box));
    collisionArea *dot_collision_area    = collision_area_load(&resources, COLLISION_AREA_DOT,    collision_area_from_game_object_parse_result(&parsed_dot));
    
    free(parsed_player.collision_area_design);
    free(parsed_box.collision_area_design);
    free(parsed_dot.collision_area_design);
    
    struct gameObject collidables[COLLIDABLE_COUNT] = {
        { .position = {.x = 0, .y = 5},  .sprite = box_sprite, .collision_area = box_collision_area },
        { .position = {.x = 10, .y = 5}, .sprite = box_sprite, .collision_area = box_collision_area },
        { .position = {.x = -10, .y = 5}, .sprite = dot_sprite, .collision_area = dot_collision_area },
    };
    struct gameState state = {
        .stop = 0,
        .resources = resources,
        .player = { .position = {.x = 0, .y = 0}, .sprite = player_sprite, .collision_area = player_collision_area },
        .collidables = create_game_objects(collidables,COLLIDABLE_COUNT),
    };
    return state;
}

void game_shutdown(struct gameState* state) {
    game_resources_free(&state->resources);
    game_objects_free(&state->collidables);
}

void game_objects_free(struct gameObjects *game_objects) {
    free(game_objects->objects);
}

void game_resources_free(struct gameResources *game_resources) {
    sprites_free(&game_resources->sprites);
    point_arrays_free(&game_resources->collision_areas);
}