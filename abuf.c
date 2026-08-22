#include <stdlib.h>
#include <string.h>

#include "abuf.h"

void abuf_append(struct abuf *abuf, const char *s, int len) {
    char *new = realloc(abuf->b, abuf->len + len);
    if (new == NULL) return;
    memcpy(&new[abuf->len], s, len);
    abuf->b = new;
    abuf->len += len;
}

void abuf_free(struct abuf *abuf) {
    free(abuf->b);
}