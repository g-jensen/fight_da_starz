#pragma once

#include "drawbuf.h"
#include "grid.h"
#include "../shared/core.h"

typedef struct window {
    int rows;
    int cols;
    draw_buf drawBuf;
} window;

int window_mmap(window *window, size_t window_drawbuf_capacity);
void window_draw(window *window, grid *grid);