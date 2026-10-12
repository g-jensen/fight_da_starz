#pragma once

typedef struct grid {
    char *chars;
    char *colors;
    int rows;
    int cols;
} grid;

int grid_mmap(grid *grid, int rows, int cols);
int grid_index(grid *grid, int row, int col);
char grid_get_char(grid *grid, int row, int col);
char* grid_get_color(grid *grid, int row, int col);
void grid_set(grid *grid, int row, int col, char c, char color[16]);
void grid_fill(grid *grid, char c, char color[16]);