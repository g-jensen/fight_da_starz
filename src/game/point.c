#include <math.h>

#include "point.h"

ipoint ipoint_add(ipoint p1, ipoint p2) {
    return (ipoint) {.x = p1.x + p2.x , .y = p1.y + p2.y};
}

ipoint ipoint_sub(ipoint p1, ipoint p2) {
    return (ipoint) {.x = p1.x - p2.x , .y = p1.y - p2.y};
}

int ipoint_eq(ipoint p1, ipoint p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

fpoint fpoint_add(fpoint p1, fpoint p2) {
    return (fpoint) {.x = p1.x + p2.x , .y = p1.y + p2.y};
}

fpoint fpoint_sub(fpoint p1, fpoint p2) {
    return (fpoint) {.x = p1.x - p2.x , .y = p1.y - p2.y};
}

int fpoint_eq(fpoint p1, fpoint p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

float magnitude(fpoint p) {
    return sqrt(p.x*p.x + p.y*p.y);
}

fpoint clamp(fpoint p, float max_magnitude) {
    float mag = magnitude(p);
    if (mag > max_magnitude) {
        return (fpoint){.x = p.x * max_magnitude / mag, .y = p.y * max_magnitude / mag};
    }
    return p;
}

ipoint to_ipoint(fpoint p) {
    return (ipoint){.x = (int)p.x, .y = (int)p.y};
}