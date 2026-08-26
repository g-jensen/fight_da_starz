#pragma once

#include <stdlib.h>
#include <sys/select.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct optional_char {
    int some;
    char value;
};

void die(const char *s);
int insert_string(char* buf, char* string);
int read_timeout(int fd, char *buf, size_t count, struct timeval timeout);