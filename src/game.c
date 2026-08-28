#include "game.h"
#include "log.h"
#include "sys.h"

long long start_tick = 0, end_tick = 0;


int get_collision_area_length(struct sprite sprite) {
    int j = 0;

    for(int i = 0; sprite.design[i] != '\0'; i++) {
        if(sprite.design[i] != '\n' && sprite.design[i] != ' ') {
            j++;
        }
    }

    return j; 
}

struct pointArray create_collision_area(struct sprite sprite) {
    struct point position = {0,0};
    int j = 0;
    int length = get_collision_area_length(sprite);
    struct point *collision_area = malloc(length*sizeof(struct point));

     for(int i = 0; sprite.design[i] != '\0'; i++) {
        if(sprite.design[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (sprite.design[i] == ' ') {
            position.x++;
            continue;
        }
        collision_area[j++] = point_sub(position, sprite.offset);
        position.x++;
    }

    return (struct pointArray){.points = collision_area, .length = length}; 
}

int is_point_in_game_object(struct point point, struct gameObject game_object) {
    for(int i = 0; i < game_object.collision_area.length; i++) {
        struct point current_object_point = point_add(game_object.collision_area.points[i], game_object.position);
        if (point_eq(point,current_object_point)) {
            return 1;
        }
    }
    return 0;
}

int are_game_objects_overlapping(struct gameObject go_0, struct gameObject go_1) {
    for(int i = 0; i < go_0.collision_area.length; i++) {
        struct point current_player_position = point_add(go_0.collision_area.points[i], go_0.position);
        
        if (is_point_in_game_object(current_player_position,go_1)) {
            return 1;
        }
    }
    return 0;
}

int is_object_overlapping(struct gameObject target, struct gameObjectArray objects) {
    for (int i = 0; i < objects.length; i++) {
        if (are_game_objects_overlapping(target,objects.game_objects[i])) {
            return 1;
        }
    }
    return 0;
}

void process_key(struct gameState *state, struct optional_char c) {
    end_tick = get_time_mus();
    state->fps = ceil_f(1000000.0f / (end_tick - start_tick));
    start_tick = get_time_mus();
    if (!c.some) return;
    struct gameObject new_player = state->player; // TODO - refactor this unnecessary copy.
    switch (c.value) {
        case 'w':
            new_player.position.y--;
            if(!is_object_overlapping(new_player, state->collidables)) {
                state->player.position.y--;
            }
            break;
        case 'a':
            new_player.position.x--;
            if(!is_object_overlapping(new_player, state->collidables)) {
                state->player.position.x--;
            }
            break;
        case 's':
            new_player.position.y++;
            if(!is_object_overlapping(new_player, state->collidables)) {
                state->player.position.y++;
            }
            break;
        case 'd':
            new_player.position.x++;
            if(!is_object_overlapping(new_player, state->collidables)) {
                state->player.position.x++;
            }
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

struct gameObjectArray create_boxes(struct gameObject game_objects[], int game_object_count) {
    struct gameObjectArray arr = {.game_objects = malloc(sizeof(struct gameObject)*game_object_count), .length = game_object_count};
    for (int i = 0 ; i < game_object_count; i++) {
        arr.game_objects[i] = game_objects[i];
    }
    return arr;
}

#define COLLIDABLE_COUNT 2

struct gameState game_init() {
    struct sprite player_sprite = sprite_create_from_file("sprites/player.txt");
    struct sprite box_sprite = sprite_create_from_file("sprites/box.txt");
    struct pointArray box_collision_area = create_collision_area(box_sprite);
    struct gameObject collidables[COLLIDABLE_COUNT] = {
        {
            .position = {.x = 0, .y = 5}, 
            .sprite = box_sprite,
            .collision_area = box_collision_area,
        },
        {
            .position = {.x = 10, .y = 5}, 
            .sprite = box_sprite,
            .collision_area = box_collision_area,
        },
    };
    struct gameState state = {
        .stop = 0, 
        .player = {
            .position = {.x = 0, .y = 0}, 
            .sprite = player_sprite, 
            .collision_area = create_collision_area(player_sprite),
        },
        .collidables = create_boxes(collidables,COLLIDABLE_COUNT),
    };

    return state;
}

void game_shutdown(struct gameState* state) {
    game_object_free(state->player);
    game_object_array_free(state->collidables);
}

void game_object_free(struct gameObject game_object) {
    sprite_free(game_object.sprite);
    point_array_free(game_object.collision_area);
}

void game_object_array_free(struct gameObjectArray game_object_array) {
    free(game_object_array.game_objects);
}