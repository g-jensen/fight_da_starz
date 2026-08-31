#include "point.h"

struct ipoint ipoint_add(struct ipoint p1, struct ipoint p2) {
    return (struct ipoint) {.x = p1.x + p2.x , .y = p1.y + p2.y};
}

struct ipoint ipoint_sub(struct ipoint p1, struct ipoint p2) {
    return (struct ipoint) {.x = p1.x - p2.x , .y = p1.y - p2.y};
}

int ipoint_eq(struct ipoint p1, struct ipoint p2) {
    return p1.x == p2.x && p1.y == p2.y;
}