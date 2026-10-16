#pragma once

#include <sys/types.h> // breaks on windows

#define COLOR_PARAM_CAPACITY 4

typedef struct color { // TODO - Linear accumulator
    u_int8_t params[COLOR_PARAM_CAPACITY];
    size_t length;
} color;

#define ESCAPE_CODE_CAPACITY 32

void color_to_escape_code(char *escape_code, color *color);