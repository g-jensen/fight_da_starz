#pragma once

struct ipoint {
    int x;
    int y;
};

struct ipoint ipoint_add(struct ipoint p1, struct ipoint p2);
struct ipoint ipoint_sub(struct ipoint p1, struct ipoint p2);
int ipoint_eq(struct ipoint p1, struct ipoint p2);