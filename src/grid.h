#pragma once

struct grid {
    char* chars;
    int rows;
    int cols;
};

int grid_mmap(struct grid *grid, int rows, int cols);
char grid_get(struct grid *grid, int row, int col);
void grid_set(struct grid *grid, int row, int col, char c);
void grid_free(struct grid *grid);
void grid_fill(struct grid *grid, char c);