#include <stdlib.h>

#include "grid.h"
#include "sys.h"

char grid_get(grid *grid, int row, int col) {
    return grid->chars[row*(grid->cols) + col];
};

void grid_set(grid *grid, int row, int col, char c) {
    grid->chars[row*(grid->cols) + col] = c;
};

int grid_mmap(grid *grid, int rows, int cols) {
    grid->rows = rows;
    grid->cols = cols;
    grid->chars = memory_map(rows*cols*sizeof(char));
    return 0;
}

void grid_fill(grid *grid, char c) {
    for (int i = 0; i < (grid->rows*grid->cols); i++) {
        grid->chars[i] = c;
    }
}