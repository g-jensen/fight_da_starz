#pragma once

#include <stdlib.h>

int read_timeout(int fd, char *buf, size_t count, long mus_timeout);
long long get_time_mus();
void musleep(long long time);
int get_terminal_size(int *width, int *height);
void* memory_map(size_t len);