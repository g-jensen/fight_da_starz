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

void place_sprite(struct point p, struct point offset, struct grid grid, char *c) {
    struct point position = {0,0};

    for(int i = 0; c[i] != '\0'; i++) {
        if(c[i] == '\n') {
            position.y++;
            position.x = 0;
            continue;
        } else if (c[i] == ' ') {
            position.x++;
            continue;
        }
        place_char(point_sub(point_add(p,position),offset), grid, c[i]);
        position.x++;
    }
}

struct point render_position(struct point p, struct point center_position, struct point real_player_position) {
    return point_sub(point_add(p, center_position), real_player_position);
}

char* build_sprite(char *filename) {
    FILE *f;
    f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *sprite = malloc(sizeof(char)*(fsize + 1));
    fread(sprite, fsize, 1, f);
    fclose(f);
    
    sprite[fsize] = '\0';
    return sprite;
}

void build_fps(struct gameState *state, char* fps, int maxlen) {
    snprintf(fps,maxlen,"FPS: %d",state->fps);
}

char *player_sprite = NULL;
char *box_sprite = NULL;

void render_state_into_grid(struct gameState *state, struct grid grid) {
    grid_fill(grid, DEFAULT_CHAR);

    if(player_sprite == NULL) {
        player_sprite = build_sprite("sprites/player.txt");
        box_sprite = build_sprite("sprites/box.txt");
    }

    struct point center_position = {.x = grid.cols/2, .y = grid.rows/2};
    struct point player_rendered_position = center_position;
    struct point box_rendered_position = render_position(state->box_position, center_position, state->player_position);
    
    place_sprite(box_rendered_position, (struct point){.x = 2, .y = 1}, grid, box_sprite);
    place_sprite(player_rendered_position, (struct point){.x = 3, .y = 2}, grid, player_sprite);

    struct point fps_rendered_position = {.x = 0, .y = 0};
    char fps[16];
    build_fps(state,fps,16);
    place_sprite(fps_rendered_position, (struct point){}, grid, fps);

    if(state->stop) {
        free(player_sprite);
        free(box_sprite);
    }
}