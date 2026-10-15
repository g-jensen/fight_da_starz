#include <stdlib.h>

#include "resources.h"
#include "core.h"
#include "sys.h"

sprite* sprite_new(resources *resources) {
    if (!(resources->sprites_buf.length < SPRITES_CAPACITY)) {
        die("sprite_new: too many sprites");
    }
    return &resources->sprites_buf.buffer[resources->sprites_buf.length++];
}

int resources_init(resources *resources) {
    *resources = (struct resources){0};
    return 0;
}