#include <stdio.h>
#include <string.h>

#include "render.h"

struct grid render_grid_create(int rows, int cols) {
    return grid_create(rows,cols, DEFAULT_CHAR);
}

void place_char(struct point p, struct grid grid, char c) {
    if(!(p.x >= grid.cols || p.y >= grid.rows || p.x < 0 || p.y < 0)){
        grid_set(grid, p.y, p.x, c);
    }
}

void place_sprite(struct point p, struct grid grid, struct sprite sprite) {
    struct point position = {0,0};

    for(int i = 0; sprite.design[i] != '\0'; i++) {
        if(sprite.design[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (sprite.design[i] == ' ') {
            position.x++;
            continue;
        }
        place_char(point_sub(point_add(p,position),sprite.offset), grid, sprite.design[i]);
        position.x++;
    }
}

struct point render_position(struct point p, struct point center_position, struct point real_player_position) {
    return point_sub(point_add(p, center_position), real_player_position);
}

struct sprite build_sprite(char *filename) {
    FILE *f;
    f = fopen(filename, "r");

    struct point offset;
    if (fscanf(f,"%d,%d",&offset.x,&offset.y) != 2) {
        die("build_sprite");
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

void free_sprite(struct sprite sprite) {
    free(sprite.design);
}

void build_fps(struct gameState *state, struct sprite fps, int maxlen) {
    snprintf(fps.design,maxlen,"FPS: %d",state->fps);
}

int has_built_sprites = 0;
struct sprite player_sprite;
struct sprite box_sprite;

void render_state_into_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);

    if(!has_built_sprites) {
        player_sprite = build_sprite("sprites/player.txt");
        box_sprite = build_sprite("sprites/box.txt");
        has_built_sprites = 1;
    }

    struct point center_position = {.x = grid.cols/2, .y = grid.rows/2};
    struct point player_rendered_position = center_position;
    struct point box_rendered_position = render_position(state->box_position, center_position, state->player_position);
    
    place_sprite(box_rendered_position, grid, box_sprite);
    place_char(box_rendered_position,grid,'x');
    place_sprite(player_rendered_position, grid, player_sprite);
    place_char(player_rendered_position,grid,'x');

    struct point fps_rendered_position = {.x = 0, .y = 0};
    char fps_design[16];
    struct sprite fps  = {.design = fps_design};
    build_fps(state,fps,16);
    place_sprite(fps_rendered_position, grid, fps);

    if(state->stop) {
        free_sprite(player_sprite);
        free_sprite(box_sprite);
    }
}