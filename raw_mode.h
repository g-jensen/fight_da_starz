#pragma once

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct terminalContext {
    struct termios orig_termios;
};

static struct terminalContext TERM_CTX;

void disable_raw_mode();
void enable_raw_mode();