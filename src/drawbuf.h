#pragma once

#include <stdlib.h>

struct drawBuf {
  char *b;
  int length;
  int capacity;
};

#define DRAWBUF_INIT {NULL, 0}

void drawbuf_free(struct drawBuf *drawBuf);