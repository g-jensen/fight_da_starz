#include <stdlib.h>
#include <unistd.h>

#include "raw_mode.h"
#include "core.h"

struct terminalContext TERM_CTX;

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &TERM_CTX.orig_termios) == -1) {
        die("tcsetattr");
    }
}

void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &TERM_CTX.orig_termios) == -1) {
        die("tcgetattr");
    }

    struct termios raw = TERM_CTX.orig_termios;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // disable BRKINT, parity checking, bit stripping, and Ctrl-M|S|Q
    raw.c_oflag &= ~(OPOST); // disable output processing (e.g. converting "\n" to "\r\n")
    raw.c_cflag |= (CS8); // set character size to 8 bits per byte
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);  // disable echo, canonical mode, and Ctrl-V|O|C|Z
    raw.c_cc[VMIN] = 0; // set minimum characters for read()
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}