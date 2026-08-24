#include "lib/libuiohook/dist/include/uiohook.h"

#include "uiohook.h"
#include "core.h"

void* uiohook_run(void*) {
    if (hook_run() != UIOHOOK_SUCCESS) {
        die("hook_run");
    }

    return NULL;
}

pthread_t uiohook_init() {
    pthread_t thread;
    pthread_create(&thread, NULL, uiohook_run, NULL);
    return thread;
}

void uiohook_shutdown(pthread_t uiohook_thread) {
    hook_stop();
    pthread_join(uiohook_thread, NULL);
}