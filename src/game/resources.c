#include <stdlib.h>

#include "resources.h"
#include "../shared/sys.h"
#include "../shared/core.h"
#include "../shared/gameobject_file.h"

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

game_object_file_resource game_object_file_load(resources *resources, char* filepath) {
    game_object_parse_result parsed;
    char *design = resources->designs_buf.buffer+resources->designs_buf.length;
    color_param_buf *param_buf = &resources->color_resources.param_buf;
    color *color = color_new(resources);
    collision_offsets_buf *offsets_buf = &resources->collision_offsets_buf;

    parse_game_object_file(&parsed, color, param_buf, design, offsets_buf, filepath);
    resources->designs_buf.length += parsed.sprite_design.length;

    sprite *sprite = sprite_new(resources);
    sprite_init_from_parsed_game_object(sprite, &parsed);

    return (game_object_file_resource){.sprite = sprite, .collision_offset = parsed.collision_offset};
}