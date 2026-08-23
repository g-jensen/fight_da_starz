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

struct windowConfig {
    int screenrows;
    int screencols;
};

void window_init();
void window_cleanup();
struct windowConfig window_init_config();
void window_buf_draw(struct drawBuf *drawBuf);
void window_grid_draw(struct grid grid, struct drawBuf drawBuf);
void window_clear_screen();
void window_hide_cursor();
void window_show_cursor();
int window_buf_reset_cursor(char* buf);
int window_buf_clear_line(char* buf);
int window_buf_new_line(char* buf);
struct optional_char window_read_key();

void grid_into_drawbuf(struct grid grid, struct drawBuf drawBuf);
struct drawBuf drawbuf_create_from_grid(struct grid grid);