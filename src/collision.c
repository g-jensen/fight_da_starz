#include "collision.h"

int collision_check_point(ipoint p, collision_area *collision_area) {
    for(int i = 0; i < collision_area->offsets.length; i++) {
        if (ipoint_eq(p,ipoint_add(collision_area->offsets.points[i], collision_area->position))) {
            return 1;
        }
    }
    return 0;
}

int collision_check_area(collision_area *ca_0, collision_area *ca_1) {
    for(int i = 0; i < ca_0->offsets.length; i++) {
        if (collision_check_point(ipoint_add(ca_0->offsets.points[i], ca_0->position), ca_1)) {
            return 1;
        }
    }
    return 0;
}

int collision_check_areas(collision_area *target, collision_area_iter *cas) {
    while(cas->more(cas->state)) {
        collision_area ca = cas->next(cas->state);
        if (collision_check_area(target,&ca)) {
            return 1;
        }
    }
    return 0;
}