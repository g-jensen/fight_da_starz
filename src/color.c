#include <stdio.h>

#include "color.h"

void color_to_escape_code(char* escape_code, color color) {
    snprintf(escape_code, ESCAPE_CODE_CAPACITY, "\033[%hhd;%hhdm", color.foreground, color.background);
}