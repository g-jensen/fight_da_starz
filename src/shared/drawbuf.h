#pragma once

#include <stdlib.h>

typedef struct draw_buf {
  char *b;
  size_t length;
  size_t capacity;
} draw_buf;