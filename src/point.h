#pragma once

struct point {
    int x;
    int y;
};

struct point point_add(struct point p1, struct point p2);
struct point point_sub(struct point p1, struct point p2);
int point_eq(struct point p1, struct point p2);