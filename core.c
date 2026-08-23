#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

int insert_string(char* buf, char* string) {
    int len = strlen(string);
    for (int k = 0; k < len; k++) {
        buf[k] = string[k];
    }
    return len;
}