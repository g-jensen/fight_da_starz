#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "core.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

int sgn_f(float f) {
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 0;
}

int ceil_f(float f) {
    return (int)ceilf(f);
}

int floor_f(float f) {
    return (int)floor(f);
}