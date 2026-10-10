#pragma once

typedef struct {
    int x;
    int y;
} ipoint;

// TODO - extract this to macros

ipoint ipoint_add(ipoint p1, ipoint p2);
ipoint ipoint_sub(ipoint p1, ipoint p2);
int ipoint_eq(ipoint p1, ipoint p2);

typedef struct {
    float x;
    float y;
} fpoint;

fpoint fpoint_add(fpoint p1, fpoint p2);
fpoint fpoint_sub(fpoint p1, fpoint p2);
int fpoint_eq(fpoint p1, fpoint p2);

float magnitude(fpoint p);
fpoint clamp(fpoint p, float max_magnitude);

ipoint to_ipoint(fpoint p);