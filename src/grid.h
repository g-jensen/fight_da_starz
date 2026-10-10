#pragma once

typedef struct {
    char* chars;
    int rows;
    int cols;
} grid;

int grid_mmap(grid *grid, int rows, int cols);
char grid_get(grid *grid, int row, int col);
void grid_set(grid *grid, int row, int col, char c);
void grid_fill(grid *grid, char c);