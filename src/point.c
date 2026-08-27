#include "point.h"

struct point point_add(struct point p1, struct point p2) {
    return (struct point) {.x = p1.x + p2.x , .y = p1.y + p2.y};
}

struct point point_sub(struct point p1, struct point p2) {
    return (struct point) {.x = p1.x - p2.x , .y = p1.y - p2.y};
}