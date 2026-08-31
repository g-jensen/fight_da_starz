#include <math.h>

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

struct fpoint fpoint_add(struct fpoint p1, struct fpoint p2) {
    return (struct fpoint) {.x = p1.x + p2.x , .y = p1.y + p2.y};
}

struct fpoint fpoint_sub(struct fpoint p1, struct fpoint p2) {
    return (struct fpoint) {.x = p1.x - p2.x , .y = p1.y - p2.y};
}

int fpoint_eq(struct fpoint p1, struct fpoint p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

float magnitude(struct fpoint p) {
    return sqrt(p.x*p.x + p.y*p.y);
}

struct ipoint to_ipoint(struct fpoint p) {
    return (struct ipoint){.x = (int)p.x, .y = (int)p.y};
}