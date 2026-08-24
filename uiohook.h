#pragma once

#include <pthread.h>

pthread_t uiohook_init();
void uiohook_shutdown(pthread_t uiohook_thread);