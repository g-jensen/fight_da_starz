#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gameobject_file.h"
#include "core.h"

typedef struct game_object_parse_result {
    ipoint offset;
    design sprite_design;
    collision_offset collision_offset;
    color color;
} game_object_parse_result;

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

design parse_design(designs_buf *designs_buf, FILE *f, int design_length) {
    long parse_start = ftell(f);
    long size = design_size(f,design_length);
    
    if (size > MAX_DESIGN_SIZE) {
        die("parse_design: size > MAX_DESIGN_SIZE");
    }

    char* design_buf_start = designs_buf->buffer+designs_buf->length;

    fseek(f, parse_start, SEEK_SET);
    fread(design_buf_start, size, 1, f);
    
    designs_buf->length += size;
    
    return (design) {
        .content = design_buf_start,
        .length = size
    };
}

void parse_game_object_header(FILE *f, ipoint *offset, int *design_length, color* color) {
    if (fscanf(f,"%d,%d\n%hhd,%hhd\n%d",&offset->x,&offset->y,&color->foreground,&color->background,design_length) != 5) {
        die("parse_game_object_header");
    }
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

void parse_game_object_file(game_object_parse_result *parsed, resources *resources, char *filepath) {
    FILE *f;
    f = fopen(filepath, "r");
    if (f == NULL) {
        die("parse_game_object_file: can't open file");
    }

    int design_length;
    parse_game_object_header(f, &parsed->offset, &design_length, &parsed->color);
    fgetc(f);

    parsed->sprite_design = parse_design(&resources->designs_buf, f,design_length);

    designs_buf collision_area_design_buf = {0};
    design collision_area_design = parse_design(&collision_area_design_buf, f, design_length);

    fclose(f);

    parsed->collision_offset = collision_offset_from_parsed_game_object(&resources->collision_offsets_buf, &collision_area_design, parsed->offset);
}

void sprite_init_from_parsed_game_object(sprite *sprite, game_object_parse_result *parse_result) {
    sprite->design = parse_result->sprite_design;
    sprite->offset = parse_result->offset;
    sprite->color = parse_result->color;
}

game_object_file_resource game_object_file_load(resources *resources, char* filepath) {
    game_object_parse_result parsed;
    parse_game_object_file(&parsed, resources, filepath);

    sprite *sprite = sprite_new(resources);
    sprite_init_from_parsed_game_object(sprite, &parsed);

    return (game_object_file_resource){.sprite = sprite, .collision_offset = parsed.collision_offset};
}