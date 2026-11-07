#pragma once

#include <stdlib.h>

typedef enum Event  {
    EVENT_NOOP,
    EVENT_QUIT,
    EVENT_PLAYER_UP,
    EVENT_PLAYER_LEFT,
    EVENT_PLAYER_RIGHT,
} Event;

// ascii ' ' to '~', plus CTRL+C (still need to support arrow keys, etc)
#define EVENTS_COUNT ((1+'~'-' ') + 1)
#define KEY(c) c-' '
#define KEY_CTRL_C '~'-' '+0
#define KEY_NOOP EVENTS_COUNT-1

extern Event EVENT_KEY_MAP[EVENTS_COUNT];

size_t char_to_event_index(char c);