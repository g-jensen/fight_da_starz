#pragma once

#include <termios.h>

struct terminalContext {
    struct termios orig_termios;
};

extern struct terminalContext TERM_CTX;

void disable_raw_mode();
void enable_raw_mode();