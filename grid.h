#pragma once

#define DEFAULT_CHAR ' '

struct grid {
    char* chars;
    int rows;
    int cols;
};

struct grid grid_create(int rows, int cols);
char grid_get(struct grid grid, int row, int col);
void grid_set(struct grid grid, int row, int col, char c);
void grid_free(struct grid grid);