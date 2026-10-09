#pragma once

#define MAX_DESIGN_SIZE 1024
#define MAX_DESIGNS_COUNT 64
#define MAX_DESIGNS_BUFFER MAX_DESIGN_SIZE*MAX_DESIGNS_COUNT

struct designs_buf {
    char buffer[MAX_DESIGNS_BUFFER];
    int length;
};

struct design {
    char *content;
    int length;
};