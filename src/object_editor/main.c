#include <stdio.h>

#include "../shared/core.h"
#include "../shared/gameobject_file.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("No file path was given.\n");
        return 1;
    }
    char* filepath = argv[1];
    game_object_parse_result parsed;
    color color;
    color_param_buf param_buf = {};
    char design[MAX_DESIGN_SIZE];
    collision_offsets_buf offsets_buf = {};
    
    parse_game_object_file(&parsed, &color, &param_buf, design, &offsets_buf, filepath);
    
    sprite sprite;
    sprite_init_from_parsed_game_object(&sprite, &parsed);

    printf("%s", sprite.design.content);
    printf("%d, %d\n", sprite.offset.x, sprite.offset.y);
    return 0;
}