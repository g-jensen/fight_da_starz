#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "core.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

int ceil_f(float f) {
    return (int)ceilf(f);
}