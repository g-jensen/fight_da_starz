#include <stdlib.h>

#include "pointarray.h"

void point_array_free(struct pointArray *point_array) {
    free(point_array->points);
}

void point_arrays_free(struct pointArrays *point_arrays) {
    for(int i = 0; i < point_arrays->length; i++) {
        point_array_free(&point_arrays->items[i]);
    }
    free(point_arrays->items);
}