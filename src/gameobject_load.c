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

char* parse_design(FILE *f, int length) {
    long design_start = ftell(f);
    long size = design_size(f,length);
    fseek(f, design_start, SEEK_SET);
    
    char *design = calloc(size + 1,sizeof(char));
    fread(design, size, 1, f);
    design[size] = '\0';
    
    return design;
}

void parse_game_object_header(FILE *f, struct ipoint *offset, int *design_length) {
    if (fscanf(f,"%d,%d\n%d",&offset->x,&offset->y,design_length) != 3) {
        die("parse_game_object_header");
    }
}

struct gameObjectParseResult parse_game_object_file(char *filepath) {
    FILE *f;
    f = fopen(filepath, "r");

    struct ipoint offset;
    int design_length;
    parse_game_object_header(f, &offset, &design_length);
    fgetc(f);

    char* sprite_design = parse_design(f,design_length);
    char* collision_area_design = parse_design(f,design_length);

    fclose(f);
    
    return (struct gameObjectParseResult){
        .offset = offset,
        .sprite_design = sprite_design,
        .collision_area_design = collision_area_design
    };
}

void game_object_parse_result_free(struct gameObjectParseResult *parse_result) {
    free(parse_result->collision_area_design);
}

struct sprite sprite_from_parsed_game_object(struct gameObjectParseResult *parse_result) {
    return (struct sprite){.design = parse_result->sprite_design, .offset = parse_result->offset};
}

int get_collision_area_length(char *design) {
    int j = 0;

    for(int i = 0; design[i] != '\0'; i++) {
        if(design[i] != '\n' && design[i] != ' ') {
            j++;
        }
    }

    return j; 
}

collisionOffset collision_offset_from_parsed_game_object(struct gameObjectParseResult *parse_result) {
    struct ipoint position = {0,0};
    int j = 0;
    int length = get_collision_area_length(parse_result->collision_area_design);
    struct ipoint *collision_area = malloc(length*sizeof(struct ipoint));

     for(int i = 0; parse_result->collision_area_design[i] != '\0'; i++) {
        if(parse_result->collision_area_design[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (parse_result->collision_area_design[i] == ' ') {
            position.x++;
            continue;
        }
        collision_area[j++] = ipoint_sub(position, parse_result->offset);
        position.x++;
    }

    return (collisionOffset){.points = collision_area, .length = length}; 
}

struct gameObjectResources load_game_object(struct resources *resources, char* filepath) {
    struct gameObjectParseResult parsed = parse_game_object_file(filepath);
    struct sprite *sprite = sprite_load(resources, sprite_from_parsed_game_object(&parsed));
    collisionOffset *collision_offset = collision_offset_load(resources, collision_offset_from_parsed_game_object(&parsed));
    game_object_parse_result_free(&parsed);
    return (struct gameObjectResources){.sprite = sprite, .collision_offset = collision_offset};
}