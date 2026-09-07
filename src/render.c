#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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

void render_format(struct grid grid, struct ipoint position, char* dest, int maxlen, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(dest,maxlen,fmt,args);
    va_end (args);
    place_sprite(position, grid, (struct sprite){.design = dest});
}

void render_state_into_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);

    struct ipoint center_position = {.x = grid.cols/2, .y = grid.rows/2};
    struct fpoint player_position = state->player.position;
    struct ipoint player_rendered_position = center_position;

    for (int i = 0; i < state->collidables.length; i++) {
        struct fpoint object_position = state->collidables.items[i].position;
        struct ipoint rendered_position = render_position(to_ipoint(object_position), center_position, to_ipoint(player_position));
        place_sprite(rendered_position, grid, *state->collidables.items[i].sprite);
    }

    place_sprite(player_rendered_position, grid, *state->player.sprite);

    char fps[32];
    render_format(grid,(struct ipoint){.y=0},fps,32,"FPS: %d",state->fps);

    char pos[32];
    render_format(grid,(struct ipoint){.y=1},pos,32,"POS: (%f,%f)",state->player.position.x,state->player.position.y);

    char vel[32];
    render_format(grid,(struct ipoint){.y=2},vel,32,"VEL: (%f,%f)",state->player.velocity.x,state->player.velocity.y);
    
    char acc[32];
    render_format(grid,(struct ipoint){.y=3},acc,32,"ACC: (%f,%f)",state->player.acceleration.x,state->player.acceleration.y);
}