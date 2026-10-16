#pragma once

#include "../shared/core.h"

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

int terminal_get_size(int *rows, int *cols);
void terminal_init();
void terminal_shutdown();
optional_char terminal_read_char(long mus_timeout);
int terminal_get_cursor_pos(int *rows, int *cols); // broken?

void terminal_hide_cursor();
void terminal_show_cursor();
void terminal_reset_cursor();
void terminal_clear_screen();