#include "../specc/specc.h"
#include "../shared/core.h"

#include "events.h"

char DEFAULT_BOUND_KEYS[] = {' ', 'w', 'a', 'd', '~', CTRL_KEY('c')};
#define DEFAULT_BOUND_KEYS_LEN sizeof(DEFAULT_BOUND_KEYS)/sizeof(DEFAULT_BOUND_KEYS[0])

int is_default_bound_key(char c) {
	for (size_t i = 0; i < DEFAULT_BOUND_KEYS_LEN; i++) {
		if (DEFAULT_BOUND_KEYS[i] == c) {
			return 1;
		}
	}
	return 0;
}

spec(char_to_event__SPACE_is_PLAYER_UP)(spec_t *s) {
	Event e = char_to_event(' ');
	should_eq(s, EVENT_PLAYER_UP, e, int);
}

spec(char_to_event__w_is_PLAYER_UP)(spec_t *s) {
	Event e = char_to_event('w');
	should_eq(s, EVENT_PLAYER_UP, e, int);
}

spec(char_to_event__a_is_PLAYER_LEFT)(spec_t *s) {
	Event e = char_to_event('a');
	should_eq(s, EVENT_PLAYER_LEFT, e, int);
}

spec(char_to_event__d_is_PLAYER_RIGHT)(spec_t *s) {
	Event e = char_to_event('d');
	should_eq(s, EVENT_PLAYER_RIGHT, e, int);
}

spec(char_to_event__CTRL_c_is_QUIT)(spec_t *s) {
	Event e = char_to_event(CTRL_KEY('c'));
	should_eq(s, EVENT_QUIT, e, int);
}

spec(char_to_event__everything_else_is_NOOP)(spec_t *s) {
	for (char c = 0; (char)(c+1) > 0; c++) {
		if (is_default_bound_key(c)) continue;
		Event e = char_to_event(c);
		should_eq(s, EVENT_NOOP, e, int);
	}
}