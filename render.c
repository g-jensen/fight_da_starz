#include "render.h"

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
}