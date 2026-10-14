#pragma once

#include <stdlib.h>

typedef struct color {
    u_int8_t foreground;
    u_int8_t background;
} color;

void color_to_escape_code(char* escape_code, color color);