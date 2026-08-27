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

int read_timeout(int fd, char *buf, size_t count, struct timeval timeout) {
    fd_set readfds;

    // Clear and set the file descriptor pool
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret < 0) {
        return -1;
    } else if (ret == 0) {
        return 0;
    } else {
        return read(fd, buf, count);
    }
}

int ceil_f(float f) {
    return ((int)f)+1;
}

suseconds_t mus(struct timeval *time) {
    return time->tv_sec*1000000 + time->tv_usec;
}