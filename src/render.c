#include <stdio.h>
#include <string.h>

#include "render.h"
#include "sprite.h"

struct grid render_grid_create(int rows, int cols) {
    return grid_create(rows,cols, DEFAULT_CHAR);
}

void place_char(struct ipoint p, struct grid grid, char c) {
    if(!(p.x >= grid.cols || p.y >= grid.rows || p.x < 0 || p.y < 0)){
        grid_set(grid, p.y, p.x, c);
    }
}

void place_sprite(struct ipoint rendered_position, struct grid grid, struct sprite sprite) {
    struct ipoint position = {0,0};

    for(int i = 0; sprite.design[i] != '\0'; i++) {
        if(sprite.design[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (sprite.design[i] == ' ') {
            position.x++;
            continue;
        }
        place_char(ipoint_sub(ipoint_add(rendered_position, position), sprite.offset), grid, sprite.design[i]);
        position.x++;
    }
}

struct ipoint render_position(struct ipoint p, struct ipoint center_position, struct ipoint real_player_position) {
    return ipoint_sub(ipoint_add(p, center_position), real_player_position);
}

void build_fps(struct gameState *state, struct sprite fps, int maxlen) {
    snprintf(fps.design,maxlen,"FPS: %d",state->fps);
}

void render_state_into_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);

    struct ipoint center_position = {.x = grid.cols/2, .y = grid.rows/2};
    struct ipoint player_rendered_position = center_position;

    for (int i = 0; i < state->collidables.length; i++) {
        struct ipoint rendered_position = render_position(state->collidables.objects[i].position, center_position, state->player.position);
        place_sprite(rendered_position, grid, *state->collidables.objects[i].sprite);
    }

    place_sprite(player_rendered_position, grid, *state->player.sprite);

    struct ipoint fps_rendered_position = {.x = 0, .y = 0};
    char fps_design[16];
    struct sprite fps  = {.design = fps_design};
    build_fps(state,fps,16);
    place_sprite(fps_rendered_position, grid, fps);
}