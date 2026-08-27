#pragma once

#include <stdlib.h>

struct drawBuf {
  char *b;
  int len;
};

#define DRAWBUF_INIT {NULL, 0}

void drawbuf_free(struct drawBuf *drawBuf);