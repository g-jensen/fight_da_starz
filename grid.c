#include <stdlib.h>

#include "grid.h"

char grid_get(struct grid grid, int row, int col) {
    return grid.chars[row*(grid.cols) + col];
};

void grid_set(struct grid grid, int row, int col, char c) {
    grid.chars[row*(grid.cols) + col] = c;
};

struct grid grid_create(int rows, int cols) {
    struct grid grid = {
        .chars = malloc(rows*cols*sizeof(char)),
        .cols = cols,
        .rows = rows
    };
    for (size_t i = 0; i < rows*cols; i++) {
        grid.chars[i] = DEFAULT_CHAR;
    }
    return grid;
};

void grid_free(struct grid grid) {
    free(grid.chars);
};