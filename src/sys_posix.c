#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "sys.h"

int read_timeout(int fd, char *buf, size_t count, long mus_timeout) {
    struct timeval timeout = {.tv_usec = mus_timeout};
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

long long get_time_mus() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec*1000000 + time.tv_usec;
}

void musleep(long long time) {
    usleep(time);
}

int get_terminal_size(int *height, int *width) {
    struct winsize ws;
    int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    *height = ws.ws_row;
    *width = ws.ws_col;
    return result;
}