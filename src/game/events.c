#include "events.h"
#include "../shared/core.h"

Event EVENT_KEY_MAP[EVENTS_COUNT] = {
    [KEY(' ')]		= EVENT_PLAYER_UP,
    [KEY('w')]		= EVENT_PLAYER_UP,
    [KEY('a')]		= EVENT_PLAYER_LEFT,
    [KEY('d')]		= EVENT_PLAYER_RIGHT,
    [KEY_CTRL_C]	= EVENT_QUIT,
    [KEY_NOOP]		= EVENT_NOOP,
};

size_t char_to_event_index(char c) {
    if (' ' <= c && c <= '~') {
        return c-' ';
    }
	if (c == CTRL_KEY('c')) { // can be generalized?
		return KEY_CTRL_C;
	}
    return KEY_NOOP;
}