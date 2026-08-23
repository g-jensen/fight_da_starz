#pragma once

#include "drawbuf.h"

// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
// https://vt100.net/docs/vt100-ug/chapter3.html#ED

#define CTRL_KEY(k) ((k) & 0x1f)

#define NEW_LINE "\r\n"

#define ESCAPE_0 '\x1b'
#define ESCAPE_1 '['

#define GET_CURSOR_POS "\x1b[6n"
#define CLEAR_SCREEN "\x1b[2J"
#define CLEAR_LINE "\x1b[K"
#define RESET_CURSOR "\x1b[H"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"

struct windowConfig {
    int screenrows;
    int screencols;
};

void window_init_config(struct windowConfig *cfg);
void window_draw_screen(struct drawBuf *drawBuf);
void window_clear_screen();
char window_read_key();
void window_hide_cursor();
void window_show_cursor();