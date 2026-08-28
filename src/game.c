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

int is_blocked(struct gameState *state, struct point new_position) {
    for(int i = 0; i < state->box.collision_area.length; i++) {
        struct point current_box_point = point_add(state->box.collision_area.points[i], state->box.position);
        
        for(int j = 0; j < state->player.collision_area.length; j++) {
            struct point current_player_position = point_add(state->player.collision_area.points[j], new_position);
            if(current_player_position.x == current_box_point.x && current_player_position.y == current_box_point.y) 
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
    struct point new_position = state->player.position;
    switch (c.value) {
        case 'w':
            new_position.y--;
            if(!is_blocked(state, new_position)) {
                state->player.position.y--;
            }
            break;
        case 'a':
            new_position.x--;
            if(!is_blocked(state, new_position)) {
                state->player.position.x--;
            }
            break;
        case 's':
            new_position.y++;
            if(!is_blocked(state, new_position)) {
                state->player.position.y++;
            }
            break;
        case 'd':
            new_position.x++;
            if(!is_blocked(state, new_position)) {
                state->player.position.x++;
            }
            break;
        case CTRL_KEY('c'):
            state->stop = 1;
            break;
    }
}

struct gameState game_init() {
    struct sprite player_sprite = sprite_create_from_file("sprites/player.txt");
    struct sprite box_sprite = sprite_create_from_file("sprites/box.txt");
    
    struct gameState state = {
        .stop = 0, 
        .player = {
            .position = {.x = 0, .y = 0}, 
            .sprite = player_sprite, 
            .collision_area = create_collision_area(player_sprite),
        },
        .box = {
            .position = {.x = 0, .y = 5}, 
            .sprite = box_sprite,
            .collision_area = create_collision_area(box_sprite),
        },
    };

    return state;
}

void game_shutdown(struct gameState* state) {
    game_object_free(state->player);
    game_object_free(state->box);
}

void game_object_free(struct gameObject game_object) {
    sprite_free(game_object.sprite);
    point_array_free(game_object.collision_area);
}