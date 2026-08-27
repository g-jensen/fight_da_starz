#include "sys.h"

#ifdef _WIN32

#include <windows.h>

int read_timeout(int fd, char *buf, size_t count, long mus_timeout) {
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

    DWORD timeout_ms = (DWORD)((mus_timeout + 999) / 1000);

    DWORD result = WaitForSingleObject(h, timeout_ms);

    if (result == WAIT_TIMEOUT)
        return 0;

    if (result != WAIT_OBJECT_0)
        return -1;

    DWORD bytes_read;

    if (!ReadFile(h, buf, (DWORD)count, &bytes_read, NULL))
        return -1;

    return (int)bytes_read;
}

long long get_time_mus() {
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;

    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);

    return (long long)(
        (counter.QuadPart * 1000000LL) / frequency.QuadPart
    );
}

void musleep(long long time) {
    // Sleep() takes milliseconds.
    Sleep((DWORD)((time + 999) / 1000));
}

int get_terminal_size(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &csbi))
        return -1;

    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 0;
}

#endif