#pragma once

#include "drawbuf.h"
#include "grid.h"
#include "core.h"

// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
// https://vt100.net/docs/vt100-ug/chapter3.html#ED

#define NEW_LINE "\r\n"

#define ESCAPE_0 '\x1b'
#define ESCAPE_1 '['

#define GET_CURSOR_POS "\x1b[6n"
#define CLEAR_SCREEN "\x1b[2J"
#define CLEAR_LINE "\x1b[K"
#define RESET_CURSOR "\x1b[H"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"

typedef struct {
    int rows;
    int cols;
    struct drawBuf drawBuf;
} window;

void window_init();
void window_shutdown();
int window_get_size(int *rows, int *cols);
int window_drawbuf_length(int rows, int cols);
int window_mmap(window *window);
void window_draw(window *window, grid *grid);
struct optional_char window_read_char(long mus_timeout);