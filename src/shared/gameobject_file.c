#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gameobject_file.h"
#include "../shared/core.h"

long design_size(FILE *f, int design_newline_count) {
    long size = 0;
    long newline_count = 0;
    char c;
    while(newline_count < design_newline_count && (c = fgetc(f)) != EOF) {
        size++;
        if (c == '\n') {
            newline_count++;
        }
    }
    return size;
}

design parse_design(char *design, FILE *f, int design_length) {
    long parse_start = ftell(f);
    long size = design_size(f,design_length);
    
    if (size > MAX_DESIGN_SIZE) {
        die("parse_design: size > MAX_DESIGN_SIZE");
    }

    char* design_buf_start = design;

    fseek(f, parse_start, SEEK_SET);
    fread(design_buf_start, size, 1, f);
    
    return (struct design) {
        .content = design_buf_start,
        .length = size
    };
}

void parse_params_into_color(FILE *f, color* color, color_param_buf* color_param_buf) {
    color->length = 0;
    char param[4] = {};
    int param_idx = 0;
    while (param_idx < 4) {
        param[param_idx] = fgetc(f);
        if (param[param_idx] == ',') {
            param[param_idx] = '\0';
            color_param_buf->buffer[color_param_buf->length+(color->length++)] = atoi(param);
            param_idx = 0;
            continue;
        }
        if (param[param_idx] == '\n') {
            param[param_idx] = '\0';
            color_param_buf->buffer[color_param_buf->length+(color->length++)] = atoi(param);
            break;
        }
        param_idx++;
    }
    color->params = color_param_buf->buffer+color_param_buf->length;
    color_param_buf->length += color->length;
}

void parse_game_object_header(FILE *f, ipoint *offset, int *design_length, color* color, color_param_buf* color_param_buf) {
    if (fscanf(f, "%d,%d", &offset->x, &offset->y) != 2) {
        die("parse_game_object_header offset");
    }
    fgetc(f);

    parse_params_into_color(f, color, color_param_buf);
    
    if (fscanf(f, "%d", design_length) != 1) {
        die("parse_game_object_header design_length");
    }
    fgetc(f);
}

int get_collision_offset_size(design* design) {
    int j = 0;

    for(size_t i = 0; i < design->length; i++) {
        if(design->content[i] != '\n' && design->content[i] != ' ') {
            j++;
        }
    }

    return j; 
}

collision_offset collision_offset_from_parsed_game_object(collision_offsets_buf *collision_offsets_buf, design *design, ipoint offset) {
    ipoint position = {0,0};
    int j = 0;
    int size = get_collision_offset_size(design);
    if (size > MAX_COLLISION_OFFSET_SIZE) {
        die("collision_offset_from_parsed_game_object: size > MAX_COLLISION_OFFSET_SIZE");
    }

    for(size_t i = 0; i < design->length; i++) {
        if(design->content[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (design->content[i] == ' ') {
            position.x++;
            continue;
        }
        if (!(collision_offsets_buf->length+j < MAX_COLLISION_OFFSETS_BUFFER)) {
            die("too many collision offsets");
        }
        collision_offsets_buf->buffer[collision_offsets_buf->length+(j++)] = ipoint_sub(position, offset);
        position.x++;
    }
    ipoint *points = collision_offsets_buf->buffer+collision_offsets_buf->length;
    collision_offsets_buf->length += size;
    return (collision_offset){.points = points, .length = size}; 
}

void parse_game_object_file(game_object_parse_result *parsed, color *color, color_param_buf *param_buf, char *design, collision_offsets_buf *offsets_buf, char *filepath) {
    FILE *f;
    f = fopen(filepath, "r");
    if (f == NULL) {
        die("parse_game_object_file: can't open file");
    }

    int design_length;
    parsed->color = color; // TODO - maybe only allocate a new color for colors that haven't already been loaded.
    parse_game_object_header(f, &parsed->offset, &design_length, parsed->color, param_buf);

    parsed->sprite_design = parse_design(design, f, design_length);

    designs_buf collision_area_design_buf = {0};
    struct design collision_area_design = parse_design(collision_area_design_buf.buffer+collision_area_design_buf.length, f, design_length);
    collision_area_design_buf.length += collision_area_design.length;
    
    fclose(f);

    parsed->collision_offset = collision_offset_from_parsed_game_object(offsets_buf, &collision_area_design, parsed->offset);
}

void sprite_init_from_parsed_game_object(sprite *sprite, game_object_parse_result *parse_result) {
    sprite->design = parse_result->sprite_design;
    sprite->offset = parse_result->offset;
    sprite->color = parse_result->color;
}