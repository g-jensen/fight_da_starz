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

struct fpoint clamp(struct fpoint p, float max_magnitude) {
    float mag = magnitude(p);
    if (mag > max_magnitude) {
        return (struct fpoint){.x = p.x * max_magnitude / mag, .y = p.y * max_magnitude / mag};
    }
    return p;
}

struct fpoint fpoint_add_clamp(struct fpoint p1, struct fpoint p2, float max_magnitude) {
    return clamp(fpoint_add(p1,p2),max_magnitude);
}

struct ipoint to_ipoint(struct fpoint p) {
    return (struct ipoint){.x = (int)p.x, .y = (int)p.y};
}