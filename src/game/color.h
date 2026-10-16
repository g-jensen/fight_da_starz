#pragma once

#define COLOR_PARAMS_CAPACITY 4
#define COLOR_BUF_CAPACITY 16
#define COLOR_PARAM_BUF_CAPACITY COLOR_PARAMS_CAPACITY*COLOR_BUF_CAPACITY

typedef int color_param;

typedef struct color_param_buf {
    color_param buffer[COLOR_PARAM_BUF_CAPACITY];
    size_t length;
} color_param_buf;

typedef struct color {
    color_param *params;
    size_t length;
} color;

typedef struct color_buf {
    color buffer[COLOR_BUF_CAPACITY];
    size_t length;
} color_buf;

#define ESCAPE_CODE_CAPACITY 32

void color_to_escape_code(char *escape_code, color *color);