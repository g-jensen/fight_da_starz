#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "render.h"
#include "sprite.h"

int render_grid_create(grid *grid, int rows, int cols) {
    grid_mmap(grid, rows,cols);
    grid_fill(grid, DEFAULT_CHAR);
    return 0;
}

void place_char(struct ipoint p, grid *grid, char c) {
    if(!(p.x >= grid->cols || p.y >= grid->rows || p.x < 0 || p.y < 0)){
        grid_set(grid, p.y, p.x, c);
    }
}

void place_sprite(struct ipoint rendered_position, grid *grid, struct sprite *sprite) {
    struct ipoint position = {0,0};

    for(int i = 0; i < sprite->design.length; i++) {
        if(sprite->design.content[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (sprite->design.content[i] == ' ') {
            position.x++;
            continue;
        }
        place_char(ipoint_sub(ipoint_add(rendered_position, position), sprite->offset), grid, sprite->design.content[i]);
        position.x++;
    }
}

struct ipoint render_position(struct ipoint p, struct ipoint center_position, struct ipoint real_player_position) {
    return ipoint_sub(ipoint_add(p, center_position), real_player_position);
}

void render_format(grid *grid, struct ipoint position, char* dest, int maxlen, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(dest,maxlen,fmt,args);
    va_end (args);
    struct sprite sprite = {
        .design = {.content = dest, .length = strlen(dest)}, 
        .offset = {.x = 0, .y = 0}
    };
    place_sprite(position, grid, &sprite);
}

void render_state_into_grid(game_state *state, grid *grid) {
    grid_fill(grid, DEFAULT_CHAR);

    struct ipoint center_position = {.x = grid->cols/2, .y = grid->rows/2};
    struct fpoint player_position = state->player.position;
    struct ipoint player_rendered_position = center_position;

    for (int i = 0; i < state->collidables.length; i++) {
        struct fpoint object_position = state->collidables.buffer[i].position;
        struct ipoint rendered_position = render_position(to_ipoint(object_position), center_position, to_ipoint(player_position));
        place_sprite(rendered_position, grid, state->collidables.buffer[i].sprite);
    }

    place_sprite(player_rendered_position, grid, state->player.sprite);

    char fps[32];
    render_format(grid,(struct ipoint){.y=0},fps,32,"FPS: %d",state->fps);

    char pos[32];
    render_format(grid,(struct ipoint){.y=1},pos,32,"POS: (%f,%f)",state->player.position.x,state->player.position.y);

    char vel[32];
    render_format(grid,(struct ipoint){.y=2},vel,32,"VEL: (%f,%f)",state->player.velocity.x,state->player.velocity.y);
    
    char acc[32];
    render_format(grid,(struct ipoint){.y=3},acc,32,"ACC: (%f,%f)",state->player.acceleration.x,state->player.acceleration.y);
}