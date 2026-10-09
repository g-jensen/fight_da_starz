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

struct gameObjectParseResult parse_game_object_file(struct designs_buf *designs_buf, char *filepath) {
    FILE *f;
    f = fopen(filepath, "r");

    struct ipoint offset;
    int design_length;
    parse_game_object_header(f, &offset, &design_length);
    fgetc(f);

    struct design sprite_design = parse_design(designs_buf, f,design_length);
    struct design collision_area_design = parse_design(designs_buf, f,design_length);

    fclose(f);
    
    return (struct gameObjectParseResult){
        .offset = offset,
        .sprite_design = sprite_design,
        .collision_area_design = collision_area_design
    };
}

struct sprite sprite_from_parsed_game_object(struct gameObjectParseResult *parse_result) {
    return (struct sprite){.design = parse_result->sprite_design, .offset = parse_result->offset};
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

collisionOffset collision_offset_from_parsed_game_object(struct gameObjectParseResult *parse_result) {
    struct ipoint position = {0,0};
    int j = 0;
    int length = get_collision_area_length(&parse_result->collision_area_design);
    struct ipoint *collision_area = malloc(length*sizeof(struct ipoint));

     for(int i = 0; i < parse_result->collision_area_design.length; i++) {
        if(parse_result->collision_area_design.content[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (parse_result->collision_area_design.content[i] == ' ') {
            position.x++;
            continue;
        }
        collision_area[j++] = ipoint_sub(position, parse_result->offset);
        position.x++;
    }

    return (collisionOffset){.points = collision_area, .length = length, .capacity = length}; 
}

struct gameObjectResources load_game_object(struct resources *resources, char* filepath) {
    struct gameObjectParseResult parsed = parse_game_object_file(&resources->designs_buf, filepath);
    struct sprite *sprite = sprite_load(resources, sprite_from_parsed_game_object(&parsed));
    collisionOffset *collision_offset = collision_offset_load(resources, collision_offset_from_parsed_game_object(&parsed));
    return (struct gameObjectResources){.sprite = sprite, .collision_offset = collision_offset};
}