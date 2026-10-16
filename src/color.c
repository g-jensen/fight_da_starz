#include <stdio.h>
#include <string.h>

#include "color.h"

void color_to_escape_code(char *escape_code, color *color) {
    size_t escape_code_length = 0;
    escape_code[escape_code_length++] = '\033';
    escape_code[escape_code_length++] = '[';
    for (size_t i = 0; i < color->length-1; i++) {
        escape_code_length += snprintf(escape_code+escape_code_length, 4, "%hhd;", color->params[i]);
    }
    escape_code_length += snprintf(escape_code+escape_code_length, 4, "%hhdm", color->params[color->length-1]);
    escape_code[escape_code_length] = '\0';
}