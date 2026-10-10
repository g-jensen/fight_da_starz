#pragma once

#define MAX_DESIGN_SIZE 1024
#define MAX_DESIGNS_COUNT 64
#define MAX_DESIGNS_BUFFER MAX_DESIGN_SIZE*MAX_DESIGNS_COUNT

typedef struct designs_buf {
    char buffer[MAX_DESIGNS_BUFFER];
    int length;
} designs_buf;

typedef struct design {
    char *content;
    int length;
} design;