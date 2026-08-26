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

struct point render_position(struct point p, struct point rendered_player_position, struct point real_player_position) {
    return point_sub(point_add(p, rendered_player_position), real_player_position);
}

void render_state_into_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);
    
    struct point player_rendered_position = {.x = grid.cols/2, .y = grid.rows/2};
    struct point box_rendered_position = render_position(state->box_position, player_rendered_position, state->player_position);
    place_char(box_rendered_position, grid, '9');
    place_char(player_rendered_position, grid, 'o');

    struct point fps_rendered_position = {.x = 0, .y = 0};
    char fps[16];
    snprintf(fps,16,"FPS: %d",state->fps);
    for (int i = 0; fps[i] != '\0'; i++) {
        place_char(point_add(fps_rendered_position, (struct point){i,0}), grid, fps[i]);
    }
}