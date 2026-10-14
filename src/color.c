#include <stdio.h>

#include "color.h"

void color_to_escape_code(char* escape_code, color color) {
    snprintf(escape_code, 16, "\033[%hhd;%hhdm", color.foreground, color.background);
}