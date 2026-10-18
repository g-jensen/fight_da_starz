#pragma once

#include "sprite.h"
#include "collision.h"
#include "design.h"
#include "color.h"

typedef struct game_object_parse_result {
    ipoint offset;
    design sprite_design;
    collision_offset collision_offset;
    color *color;
} game_object_parse_result;

void parse_game_object_file(game_object_parse_result *parsed, color *color, color_param_buf *param_buf, char* design, collision_offsets_buf *offsets_buf, char *filepath);
void sprite_init_from_parsed_game_object(sprite *sprite, game_object_parse_result *parse_result);