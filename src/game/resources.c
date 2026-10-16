#include <stdlib.h>

#include "resources.h"
#include "../shared/core.h"
#include "sys.h"
#include "gameobject_file.h"

sprite* sprite_new(resources *resources) {
    if (!(resources->sprites_buf.length < SPRITES_CAPACITY)) {
        die("sprite_new: too many sprites");
    }
    return &resources->sprites_buf.buffer[resources->sprites_buf.length++];
}

color* color_new(resources *resources) {
    if (!(resources->color_resources.color_buf.length < COLOR_BUF_CAPACITY)) {
        die("color_new: too many colors");
    }
    return &resources->color_resources.color_buf.buffer[resources->color_resources.color_buf.length++];
}

int resources_init(resources *resources) {
    *resources = (struct resources){0};
    return 0;
}

resources_ref resources_load(resources *resources) {
    resources_init(resources);
    return (resources_ref){
        .player = game_object_file_load(resources,"game_objects/player.txt"),
        .box = game_object_file_load(resources,"game_objects/box.txt"),
        .dot = game_object_file_load(resources,"game_objects/dot.txt"),
        .floor = game_object_file_load(resources,"game_objects/floor.txt"),
    };
}