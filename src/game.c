#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "log.h"
#include "sys.h"

int is_point_in_game_object(struct ipoint ipoint, struct gameObject *game_object) {
    for(int i = 0; i < game_object->collision_area->length; i++) {
        struct ipoint current_object_point = ipoint_add(game_object->collision_area->points[i], to_ipoint(game_object->position));
        if (ipoint_eq(ipoint,current_object_point)) {
            return 1;
        }
    }
    return 0;
}

int are_game_objects_overlapping(struct gameObject *go_0, struct gameObject *go_1) {
    for(int i = 0; i < go_0->collision_area->length; i++) {
        struct ipoint current_player_position = ipoint_add(go_0->collision_area->points[i], to_ipoint(go_0->position));
        
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

#define MUS_PER_SEC 1000000

long long start_tick = 0, end_tick = 0;
int iterate_fps_counters(long long *start_tick, long long *end_tick) {
    *end_tick = get_time_mus();
    int fps = ceil_f((float)MUS_PER_SEC / (*end_tick - *start_tick));
    *start_tick = get_time_mus();
    return fps;
}

#define MAX_SPEED 15

void update_state(struct gameState *state, struct optional_char c) {
    state->fps = iterate_fps_counters(&start_tick, &end_tick);

    struct gameObject new_player = state->player; // TODO - refactor this unnecessary copy.
    new_player.velocity = fpoint_add_clamp(new_player.velocity,new_player.acceleration,MAX_SPEED);
    new_player.position = fpoint_add(new_player.position,new_player.velocity);
    if (!is_object_overlapping(&new_player, &state->collidables)) {
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
            float sign = 0;
            // if (state->player.velocity.x > 0) {
            //     sign = 1;
            // } else if (state->player.velocity.x < 0) {
            //     sign = -1;
            // }
            sign = state->player.velocity.x*0.5;
            state->player.acceleration.x = -sign;
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
    SPRITE_FLOOR,
    SPRITE_END,
};

enum collisionAreaIndex {
    COLLISION_AREA_PLAYER,
    COLLISION_AREA_BOX,
    COLLISION_AREA_DOT,
    COLLISION_AREA_FLOOR,
    COLLISION_AREA_END,
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

#define COLLIDABLE_COUNT 4
#define COLLISION_AREA_COUNT COLLISION_AREA_END
#define SPRITE_COUNT SPRITE_END

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