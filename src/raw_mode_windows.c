#include "core.h"

#ifdef _WIN32

#include <windows.h>

static DWORD orig_console_mode;

void disable_raw_mode() {
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!SetConsoleMode(hstdin, orig_console_mode)) {
        die("SetConsoleMode");
    }
}

void enable_raw_mode() {
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!GetConsoleMode(hstdin, &orig_console_mode)) {
        die("GetConsoleMode");
    }

    DWORD raw = orig_console_mode;

    raw &= ~(ENABLE_ECHO_INPUT |
             ENABLE_LINE_INPUT |
             ENABLE_PROCESSED_INPUT);

    if (!SetConsoleMode(hstdin, raw)) {
        die("SetConsoleMode");
    }
}

#endif