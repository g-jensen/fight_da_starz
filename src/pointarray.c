#include <stdlib.h>

#include "pointarray.h"

void point_array_free(struct pointArray point_array) {
    free(point_array.points);
}