#pragma once

#include <stdlib.h>

typedef struct draw_buf {
  char *b;
  int length;
  int capacity;
} draw_buf;