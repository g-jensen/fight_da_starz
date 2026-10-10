#include <stdlib.h>
#include <stdio.h>

#include "gameobject_load.h"
#include "core.h"

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

struct design parse_design(struct designs_buf *designs_buf, FILE *f, int design_length) {
    long parse_start = ftell(f);
    long size = design_size(f,design_length);
    
    if (size > MAX_DESIGN_SIZE) {
        die("parse_design: size > MAX_DESIGN_SIZE");
    }

    char* design_buf_start = designs_buf->buffer+designs_buf->length;

    fseek(f, parse_start, SEEK_SET);
    fread(design_buf_start, size, 1, f);
    
    designs_buf->length += size;
    
    return (struct design) {
        .content = design_buf_start,
        .length = size
    };
}

void parse_game_object_header(FILE *f, struct ipoint *offset, int *design_length) {
    if (fscanf(f,"%d,%d\n%d",&offset->x,&offset->y,design_length) != 3) {
        die("parse_game_object_header");
    }
}

int get_collision_area_length(struct design* design) {
    int j = 0;

    for(int i = 0; i < design->length; i++) {
        if(design->content[i] != '\n' && design->content[i] != ' ') {
            j++;
        }
    }

    return j; 
}

struct collision_offset collision_offset_from_parsed_game_object(struct collision_offsets_buf *collision_offsets_buf, struct design *design, struct ipoint offset) {
    struct ipoint position = {0,0};
    int j = 0;
    int length = get_collision_area_length(design);
    if (length > MAX_COLLISION_OFFSET_SIZE) {
        die("collision_offset_from_parsed_game_object: length > MAX_COLLISION_OFFSET_SIZE");
    }

    for(int i = 0; i < design->length; i++) {
        if(design->content[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (design->content[i] == ' ') {
            position.x++;
            continue;
        }
        collision_offsets_buf->buffer[collision_offsets_buf->length+(j++)] = ipoint_sub(position, offset);
        position.x++;
    }
    struct ipoint *points = collision_offsets_buf->buffer+collision_offsets_buf->length;
    collision_offsets_buf->length += length;
    return (struct collision_offset){.points = points, .length = length}; 
}

struct gameObjectParseResult parse_game_object_file(struct designs_buf *designs_buf, struct collision_offsets_buf *collision_offsets_buf, char *filepath) {
    FILE *f;
    f = fopen(filepath, "r");

    struct ipoint offset;
    int design_length;
    parse_game_object_header(f, &offset, &design_length);
    fgetc(f);

    struct design sprite_design = parse_design(designs_buf, f,design_length);

    struct designs_buf collision_area_design_buf = {0};
    struct design collision_area_design = parse_design(&collision_area_design_buf, f, design_length);

    fclose(f);

    return (struct gameObjectParseResult){
        .offset = offset,
        .sprite_design = sprite_design,
        .collision_offset = collision_offset_from_parsed_game_object(collision_offsets_buf, &collision_area_design, offset)
    };
}

struct sprite sprite_from_parsed_game_object(struct gameObjectParseResult *parse_result) {
    return (struct sprite){.design = parse_result->sprite_design, .offset = parse_result->offset};
}

struct gameObjectResources load_game_object(struct resources *resources, char* filepath) {
    struct gameObjectParseResult parsed = parse_game_object_file(&resources->designs_buf, &resources->collision_offsets_buf, filepath);
    struct sprite *sprite = sprite_load(resources, sprite_from_parsed_game_object(&parsed));
    return (struct gameObjectResources){.sprite = sprite, .collision_offset = parsed.collision_offset};
}