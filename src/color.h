#pragma once

#include <sys/types.h> // breaks on windows

typedef struct color {
    u_int8_t foreground;
    u_int8_t background;
} color;

#define ESCAPE_CODE_CAPACITY 16

void color_to_escape_code(char* escape_code, color color);