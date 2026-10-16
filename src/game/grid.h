#pragma once

#include "color.h"

typedef struct grid {
    char *chars;
    color **colors;
    int rows;
    int cols;
} grid;

int grid_mmap(grid *grid, int rows, int cols);
int grid_index(grid *grid, int row, int col);
char grid_get_char(grid *grid, int row, int col);
color* grid_get_color(grid *grid, int row, int col);
void grid_set(grid *grid, int row, int col, char c, color *color);
void grid_fill(grid *grid, char c, color *color);