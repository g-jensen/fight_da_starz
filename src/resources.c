#include <stdlib.h>

#include "resources.h"
#include "core.h"
#include "sys.h"

#define MAX_SPRITE_COUNT 8
#define MAX_COLLISION_OFFSET_COUNT 8

sprite* sprite_get(resources *resources, int sprite_index) {
    return &resources->sprites_buf.buffer[sprite_index];
}

sprite* sprite_load(resources *resources, sprite sprite) {
    if (!(resources->sprites_buf.length < SPRITES_CAPACITY)) {
        die("sprite_load: too many sprites_buf");
    }
    resources->sprites_buf.buffer[resources->sprites_buf.length] = sprite;
    struct sprite *ptr = sprite_get(resources,resources->sprites_buf.length);
    resources->sprites_buf.length++;
    return ptr;
}

int resources_init(resources *resources) {
    *resources = (struct resources){0};
    return 0;
}