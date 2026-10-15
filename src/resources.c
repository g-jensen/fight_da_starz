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

resources_ref resources_load(resources *resources) {
    return (resources_ref){
        .player = game_object_file_load(resources,"game_objects/player.txt"),
        .box = game_object_file_load(resources,"game_objects/box.txt"),
        .dot = game_object_file_load(resources,"game_objects/dot.txt"),
        .floor = game_object_file_load(resources,"game_objects/floor.txt"),
    };
}