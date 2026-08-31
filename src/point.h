#pragma once

struct ipoint {
    int x;
    int y;
};

// TODO - extract this to macros

struct ipoint ipoint_add(struct ipoint p1, struct ipoint p2);
struct ipoint ipoint_sub(struct ipoint p1, struct ipoint p2);
int ipoint_eq(struct ipoint p1, struct ipoint p2);

struct fpoint {
    float x;
    float y;
};

struct fpoint fpoint_add(struct fpoint p1, struct fpoint p2);
struct fpoint fpoint_sub(struct fpoint p1, struct fpoint p2);
int fpoint_eq(struct fpoint p1, struct fpoint p2);
float magnitude(struct fpoint p);

struct ipoint to_ipoint(struct fpoint p);