#pragma once

#include "lib/libuiohook/include/uiohook.h"

struct vc_range {
    uint16_t first;
    uint16_t last;
    const char *const *names;
};

const char *keycode_to_name(uint16_t vc);