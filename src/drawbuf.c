#include <stdlib.h>
#include <string.h>

#include "drawbuf.h"

void drawbuf_free(struct drawBuf *drawBuf) {
    if (drawBuf->b == NULL) return;
    free(drawBuf->b);
}