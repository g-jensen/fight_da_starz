#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

int ceil_f(float f) {
    return ((int)f)+1;
}