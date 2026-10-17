#pragma once

#include <stdlib.h>

#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct optional_char {
    int some;
    char value;
} optional_char;

void die(const char *s);
int sgn_f(float f);
int ceil_f(float f);
int floor_f(float f);