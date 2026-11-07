#pragma once

extern char* LOG_FILE;

void log_info(const char *fmt, ...);
void log_raw(const char *fmt, ...);