#include <stdlib.h>
#include <stdio.h>

#include "sprite.h"
#include "core.h"

struct sprite sprite_create_from_file(char *filename) {
    FILE *f;
    f = fopen(filename, "r");

    struct point offset;
    if (fscanf(f,"%d,%d",&offset.x,&offset.y) != 2) {
        die("sprite_create_from_file");
    }

    long design_start = ftell(f);
    fseek(f, 0, SEEK_END);
    long design_size = ftell(f) - design_start + 1;
    fseek(f, design_start+1, SEEK_SET);
    
    char *sprite = malloc(sizeof(char)*(design_size + 1));
    fread(sprite, design_size, 1, f);
    fclose(f);
    
    sprite[design_size] = '\0';
    return (struct sprite){.design = sprite, .offset = offset};
}

void sprite_free(struct sprite sprite) {
    free(sprite.design);
}