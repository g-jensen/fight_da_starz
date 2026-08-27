#include <stdlib.h>

#include "grid.h"

char grid_get(struct grid grid, int row, int col) {
    return grid.chars[row*(grid.cols) + col];
};

void grid_set(struct grid grid, int row, int col, char c) {
    grid.chars[row*(grid.cols) + col] = c;
};

struct grid grid_create(int rows, int cols, char fill_char) {
    struct grid grid = {
        .chars = malloc(rows*cols*sizeof(char)),
        .cols = cols,
        .rows = rows
    };
    grid_fill(grid, fill_char);
    return grid;
};

void grid_free(struct grid grid) {
    free(grid.chars);
};

void grid_fill(struct grid grid, char c) {
    for (int i = 0; i < (grid.rows*grid.cols); i++) {
        grid.chars[i] = c;
    }
}