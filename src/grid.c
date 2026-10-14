#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "sys.h"

int grid_index(grid *grid, int row, int col) {
    return row*(grid->cols) + col;
}

char grid_get_char(grid *grid, int row, int col) {
    return grid->chars[grid_index(grid, row, col)];
};

color* grid_get_color(grid *grid, int row, int col) {
    return &grid->colors[grid_index(grid, row, col)];
};

void grid_set(grid *grid, int row, int col, char c, color color) {
    int index = grid_index(grid, row, col);
    grid->chars[index] = c;
    grid->colors[index] = color;
};

int grid_mmap(grid *grid, int rows, int cols) {
    grid->rows = rows;
    grid->cols = cols;
    grid->chars = memory_map(rows*cols*sizeof(char));
    grid->colors = memory_map(rows*cols*sizeof(color));
    return 0;
}

void grid_fill(grid *grid, char c, color color) {
    for (int i = 0; i < (grid->rows*grid->cols); i++) {
        grid->chars[i] = c;
        grid->colors[i] = color;
    }
}