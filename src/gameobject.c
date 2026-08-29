#include <stdlib.h>
#include <stdio.h>

#include "gameobject.h"
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

struct gameObjectParseResult parse_game_object_file(char *filename) {
    FILE *f;
    f = fopen(filename, "r");

    struct point offset;
    int design_length;
    if (fscanf(f,"%d,%d\n%d",&offset.x,&offset.y,&design_length) != 3) {
        die("parse_game_object_file");
    }    
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

struct sprite sprite_from_game_object_parse_result(struct gameObjectParseResult *parse_result) {
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

collisionArea collision_area_from_game_object_parse_result(struct gameObjectParseResult *parse_result) {
    struct point position = {0,0};
    int j = 0;
    int length = get_collision_area_length(parse_result->collision_area_design);
    struct point *collision_area = malloc(length*sizeof(struct point));

     for(int i = 0; parse_result->collision_area_design[i] != '\0'; i++) {
        if(parse_result->collision_area_design[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (parse_result->collision_area_design[i] == ' ') {
            position.x++;
            continue;
        }
        collision_area[j++] = point_sub(position, parse_result->offset);
        position.x++;
    }

    return (collisionArea){.points = collision_area, .length = length}; 
}