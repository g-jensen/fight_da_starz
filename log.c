#include <stdio.h>

#include <stdarg.h>

#include "log.h"
#include "core.h"

extern char* LOG_FILE;

void log_info(const char *fmt, ...) {
    FILE* f = fopen(LOG_FILE,"a");
    if (f == NULL) {
        fclose(f);
        die("log_info");
    } else {
        fprintf(f,"[LOG_INFO] ");
        va_list args;
        va_start(args, fmt);
        vfprintf (f, fmt, args);
        va_end (args);
        fprintf(f,"\n");
    }
    fclose(f); // fix later, we shouldn't be closing after every log.
}