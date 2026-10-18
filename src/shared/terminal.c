#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "terminal.h"
#include "raw_mode.h"
#include "sys.h"

void terminal_hide_cursor() {
    write(STDOUT_FILENO, HIDE_CURSOR, 6);
}

void terminal_show_cursor() {
    write(STDOUT_FILENO, SHOW_CURSOR, 6);
}

void terminal_reset_cursor() {
    write(STDOUT_FILENO, RESET_CURSOR, 3);
}

void terminal_clear_screen() {
    write(STDOUT_FILENO, CLEAR_SCREEN, 4);
    terminal_reset_cursor();
}

void terminal_init() {
    enable_raw_mode();
    terminal_hide_cursor();
}

void terminal_shutdown() {
    terminal_show_cursor();
    terminal_clear_screen();
    disable_raw_mode();
}

optional_char terminal_read_char(long mus_timeout) {
    int nread;
    char c;
    nread = read_timeout(STDIN_FILENO, &c, 1, mus_timeout);
    if (nread == 0) return (optional_char){.some = 0};
    if (nread == -1 && errno != EAGAIN) die("terminal_read_char");
    return (optional_char){.some = 1, .value = c};
}

int terminal_get_cursor_pos(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, GET_CURSOR_POS, 4) != 4) return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

    if (buf[0] != ESCAPE_0 || buf[1] != ESCAPE_1) return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
    return 0;
}

int terminal_get_size(int *rows, int *cols) {
    if (get_terminal_size(rows,cols) == -1 || *cols == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // set cursor position to 999,999. And actually, I think this is broken.
        return terminal_get_cursor_pos(rows, cols);
    }
    return 0;
}