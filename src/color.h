#pragma once

#include <sys/types.h> // breaks on windows

typedef struct color { // TODO - I don't think order actually matters for escape codes. And there should be more than two parameters
    u_int8_t foreground;
    u_int8_t background;
} color;

#define ESCAPE_CODE_CAPACITY 16

void color_to_escape_code(char* escape_code, color color);