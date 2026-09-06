#include "gameobject_load.h"

struct gameObjectResources load_game_object(struct resources *resources, char* filepath) {
    struct gameObjectParseResult parsed = parse_game_object_file(filepath);
    struct sprite *sprite = sprite_load(resources, sprite_from_parsed_game_object(&parsed));
    collisionOffset *collision_offset = collision_offset_load(resources, collision_offset_from_parsed_game_object(&parsed));
    game_object_parse_result_free(&parsed);
    return (struct gameObjectResources){.sprite = sprite, .collision_offset = collision_offset};
}