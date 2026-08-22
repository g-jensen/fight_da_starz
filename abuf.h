#pragma once

#include <stdlib.h>

struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT {NULL, 0}

void abuf_append(struct abuf *abuf, const char *s, int len);
void abuf_free(struct abuf *abuf);