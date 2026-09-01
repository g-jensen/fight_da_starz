#include "collision.h"

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