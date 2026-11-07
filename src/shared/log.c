#include <stdio.h>
#include <stdarg.h>

#include "log.h"
#include "../shared/core.h"

char* LOG_FILE = "log.txt";

void log_info(const char *fmt, ...) {
    FILE* f = fopen(LOG_FILE,"a");
    if (f == NULL) {
        die("log_info");
    } else {
        fprintf(f,"[LOG_INFO] ");
        va_list args;
        va_start(args, fmt);
        vfprintf (f, fmt, args);
        va_end (args);
    }
    fclose(f); // fix later, we shouldn't be closing after every log.
}

void log_raw(const char *fmt, ...) {
    FILE* f = fopen(LOG_FILE,"a");
    if (f == NULL) {
        die("log_raw");
    } else {
        va_list args;
        va_start(args, fmt);
        vfprintf (f, fmt, args);
        va_end (args);
    }
    fclose(f);
}