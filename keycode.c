#include <stdlib.h>

#include "keycode.h"

int my_array[] = {
    [0] = 3,
    [100] = 10
};

static const char *const vc_0000_0046[] = {
    [VC_UNDEFINED       - VC_UNDEFINED] = "undefined",
    [VC_ESCAPE          - VC_UNDEFINED] = "escape",
    [VC_1               - VC_UNDEFINED] = "1",
    [VC_2               - VC_UNDEFINED] = "2",
    [VC_3               - VC_UNDEFINED] = "3",
    [VC_4               - VC_UNDEFINED] = "4",
    [VC_5               - VC_UNDEFINED] = "5",
    [VC_6               - VC_UNDEFINED] = "6",
    [VC_7               - VC_UNDEFINED] = "7",
    [VC_8               - VC_UNDEFINED] = "8",
    [VC_9               - VC_UNDEFINED] = "9",
    [VC_0               - VC_UNDEFINED] = "0",
    [VC_MINUS           - VC_UNDEFINED] = "minus",
    [VC_EQUALS          - VC_UNDEFINED] = "equals",
    [VC_BACKSPACE       - VC_UNDEFINED] = "backspace",
    [VC_TAB             - VC_UNDEFINED] = "tab",
    [VC_Q               - VC_UNDEFINED] = "q",
    [VC_W               - VC_UNDEFINED] = "w",
    [VC_E               - VC_UNDEFINED] = "e",
    [VC_R               - VC_UNDEFINED] = "r",
    [VC_T               - VC_UNDEFINED] = "t",
    [VC_Y               - VC_UNDEFINED] = "y",
    [VC_U               - VC_UNDEFINED] = "u",
    [VC_I               - VC_UNDEFINED] = "i",
    [VC_O               - VC_UNDEFINED] = "o",
    [VC_P               - VC_UNDEFINED] = "p",
    [VC_OPEN_BRACKET    - VC_UNDEFINED] = "open bracket",
    [VC_CLOSE_BRACKET   - VC_UNDEFINED] = "close bracket",
    [VC_ENTER           - VC_UNDEFINED] = "enter",
    [VC_CONTROL_L       - VC_UNDEFINED] = "left control",
    [VC_A               - VC_UNDEFINED] = "a",
    [VC_S               - VC_UNDEFINED] = "s",
    [VC_D               - VC_UNDEFINED] = "d",
    [VC_F               - VC_UNDEFINED] = "f",
    [VC_G               - VC_UNDEFINED] = "g",
    [VC_H               - VC_UNDEFINED] = "h",
    [VC_J               - VC_UNDEFINED] = "j",
    [VC_K               - VC_UNDEFINED] = "k",
    [VC_L               - VC_UNDEFINED] = "l",
    [VC_SEMICOLON       - VC_UNDEFINED] = "semicolon",
    [VC_QUOTE           - VC_UNDEFINED] = "quote",
    [VC_BACKQUOTE       - VC_UNDEFINED] = "backquote",
    [VC_SHIFT_L         - VC_UNDEFINED] = "left shift",
    [VC_BACK_SLASH      - VC_UNDEFINED] = "backslash",
    [VC_Z               - VC_UNDEFINED] = "z",
    [VC_X               - VC_UNDEFINED] = "x",
    [VC_C               - VC_UNDEFINED] = "c",
    [VC_V               - VC_UNDEFINED] = "v",
    [VC_B               - VC_UNDEFINED] = "b",
    [VC_N               - VC_UNDEFINED] = "n",
    [VC_M               - VC_UNDEFINED] = "m",
    [VC_COMMA           - VC_UNDEFINED] = "comma",
    [VC_PERIOD          - VC_UNDEFINED] = "period",
    [VC_SLASH           - VC_UNDEFINED] = "slash",
    [VC_SHIFT_R         - VC_UNDEFINED] = "right shift",
    [VC_KP_MULTIPLY     - VC_UNDEFINED] = "keypad multiply",
    [VC_ALT_L           - VC_UNDEFINED] = "left alt",
    [VC_SPACE           - VC_UNDEFINED] = "space",
    [VC_CAPS_LOCK       - VC_UNDEFINED] = "caps lock",
    [VC_F1              - VC_UNDEFINED] = "F1",
    [VC_F2              - VC_UNDEFINED] = "F2",
    [VC_F3              - VC_UNDEFINED] = "F3",
    [VC_F4              - VC_UNDEFINED] = "F4",
    [VC_F5              - VC_UNDEFINED] = "F5",
    [VC_F6              - VC_UNDEFINED] = "F6",
    [VC_F7              - VC_UNDEFINED] = "F7",
    [VC_F8              - VC_UNDEFINED] = "F8",
    [VC_F9              - VC_UNDEFINED] = "F9",
    [VC_F10             - VC_UNDEFINED] = "F10",
    [VC_SCROLL_LOCK     - VC_UNDEFINED] = "scroll lock",
    [VC_NUM_LOCK        - VC_UNDEFINED] = "num lock",
};

static const char *const vc_0047_0053[] = {
    [VC_KP_7             - VC_KP_7] = "keypad 7",
    [VC_KP_8             - VC_KP_7] = "keypad 8",
    [VC_KP_9             - VC_KP_7] = "keypad 9",
    [VC_KP_SUBTRACT      - VC_KP_7] = "keypad subtract",
    [VC_KP_4             - VC_KP_7] = "keypad 4",
    [VC_KP_5             - VC_KP_7] = "keypad 5",
    [VC_KP_6             - VC_KP_7] = "keypad 6",
    [VC_KP_ADD           - VC_KP_7] = "keypad add",
    [VC_KP_1             - VC_KP_7] = "keypad 1",
    [VC_KP_2             - VC_KP_7] = "keypad 2",
    [VC_KP_3             - VC_KP_7] = "keypad 3",
    [VC_KP_0             - VC_KP_7] = "keypad 0",
    [VC_KP_SEPARATOR     - VC_KP_7] = "keypad separator",
};

static const char *const vc_0057_0058[] = {
    [VC_F11 - VC_F11] = "F11",
    [VC_F12 - VC_F11] = "F12",
};

static const char *const vc_005b_005d[] = {
    [VC_F13 - VC_F13] = "F13",
    [VC_F14 - VC_F13] = "F14",
    [VC_F15 - VC_F13] = "F15",
};

static const char *const vc_0063_006b[] = {
    [VC_F16 - VC_F16] = "F16",
    [VC_F17 - VC_F16] = "F17",
    [VC_F18 - VC_F16] = "F18",
    [VC_F19 - VC_F16] = "F19",
    [VC_F20 - VC_F16] = "F20",
    [VC_F21 - VC_F16] = "F21",
    [VC_F22 - VC_F16] = "F22",
    [VC_F23 - VC_F16] = "F23",
    [VC_F24 - VC_F16] = "F24",
};

static const char *const vc_0070[] = {
    [VC_KATAKANA - VC_KATAKANA] = "katakana",
};

static const char *const vc_0073[] = {
    [VC_UNDERSCORE - VC_UNDERSCORE] = "underscore",
};

static const char *const vc_0077[] = {
    [VC_FURIGANA - VC_FURIGANA] = "furigana",
};

static const char *const vc_0079[] = {
    [VC_KANJI - VC_KANJI] = "kanji",
};

static const char *const vc_007b[] = {
    [VC_HIRAGANA - VC_HIRAGANA] = "hiragana",
};

static const char *const vc_007d_007e[] = {
    [VC_YEN      - VC_YEN] = "yen",
    [VC_KP_COMMA - VC_YEN] = "keypad comma",
};

static const char *const vc_0e0d[] = {
    [VC_KP_EQUALS - VC_KP_EQUALS] = "keypad equals",
};

static const char *const vc_0e1c_0e1d[] = {
    [VC_KP_ENTER   - VC_KP_ENTER] = "keypad enter",
    [VC_CONTROL_R  - VC_KP_ENTER] = "right control",
};

static const char *const vc_0e35[] = {
    [VC_KP_DIVIDE - VC_KP_DIVIDE] = "keypad divide",
};

static const char *const vc_0e37_0e38[] = {
    [VC_PRINTSCREEN - VC_PRINTSCREEN] = "print screen",
    [VC_ALT_R       - VC_PRINTSCREEN] = "right alt",
};

static const char *const vc_0e45_0e47[] = {
    [VC_PAUSE          - VC_PAUSE] = "pause",
    [VC_LESSER_GREATER - VC_PAUSE] = "lesser/greater",
    [VC_HOME           - VC_PAUSE] = "home",
};

static const char *const vc_0e49[] = {
    [VC_PAGE_UP - VC_PAGE_UP] = "page up",
};

static const char *const vc_0e4f[] = {
    [VC_END - VC_END] = "end",
};

static const char *const vc_0e51_0e53[] = {
    [VC_PAGE_DOWN - VC_PAGE_DOWN] = "page down",
    [VC_INSERT    - VC_PAGE_DOWN] = "insert",
    [VC_DELETE    - VC_PAGE_DOWN] = "delete",
};

static const char *const vc_0e5b_0e5d[] = {
    [VC_META_L       - VC_META_L] = "left meta",
    [VC_META_R       - VC_META_L] = "right meta",
    [VC_CONTEXT_MENU - VC_META_L] = "context menu",
};

static const char *const vc_e010[] = {
    [VC_MEDIA_PREVIOUS - VC_MEDIA_PREVIOUS] = "media previous",
};

static const char *const vc_e019[] = {
    [VC_MEDIA_NEXT - VC_MEDIA_NEXT] = "media next",
};

static const char *const vc_e020_e024[] = {
    [VC_VOLUME_MUTE    - VC_VOLUME_MUTE] = "volume mute",
    [VC_APP_CALCULATOR - VC_VOLUME_MUTE] = "app calculator",
    [VC_MEDIA_PLAY     - VC_VOLUME_MUTE] = "media play",
    [VC_MEDIA_STOP     - VC_VOLUME_MUTE] = "media stop",
};

static const char *const vc_e02c[] = {
    [VC_MEDIA_EJECT - VC_MEDIA_EJECT] = "media eject",
};

static const char *const vc_e02e[] = {
    [VC_VOLUME_DOWN - VC_VOLUME_DOWN] = "volume down",
};

static const char *const vc_e030_e032[] = {
    [VC_VOLUME_UP   - VC_VOLUME_UP] = "volume up",
    [VC_BROWSER_HOME - VC_VOLUME_UP] = "browser home",
};

static const char *const vc_e03c[] = {
    [VC_APP_MUSIC - VC_APP_MUSIC] = "app music",
};

static const char *const vc_e048[] = {
    [VC_UP - VC_UP] = "up",
};

static const char *const vc_e04b_e04d[] = {
    [VC_LEFT  - VC_LEFT] = "left",
    [VC_CLEAR - VC_LEFT] = "clear",
    [VC_RIGHT - VC_LEFT] = "right",
};

static const char *const vc_e050[] = {
    [VC_DOWN - VC_DOWN] = "down",
};

static const char *const vc_e05e_e05f[] = {
    [VC_POWER - VC_POWER] = "power",
    [VC_SLEEP - VC_POWER] = "sleep",
};

static const char *const vc_e063_e06a[] = {
    [VC_WAKE            - VC_WAKE] = "wake",
    [VC_APP_PICTURES    - VC_WAKE] = "app pictures",
    [VC_BROWSER_SEARCH  - VC_WAKE] = "browser search",
    [VC_BROWSER_FAVORITES - VC_WAKE] = "browser favorites",
    [VC_BROWSER_REFRESH - VC_WAKE] = "browser refresh",
    [VC_BROWSER_STOP    - VC_WAKE] = "browser stop",
    [VC_BROWSER_FORWARD - VC_WAKE] = "browser forward",
    [VC_BROWSER_BACK    - VC_WAKE] = "browser back",
};

static const char *const vc_e06c_e06d[] = {
    [VC_APP_MAIL     - VC_APP_MAIL] = "app mail",
    [VC_MEDIA_SELECT - VC_APP_MAIL] = "media select",
};

static const char *const vc_ee47_ee49[] = {
    [(VC_KP_HOME)    - (VC_KP_HOME)] = "keypad home",
    [(VC_KP_UP)      - (VC_KP_HOME)] = "keypad up",
    [(VC_KP_PAGE_UP) - (VC_KP_HOME)] = "keypad page up",
};

static const char *const vc_ee4b_ee4d[] = {
    [(VC_KP_LEFT)  - (VC_KP_LEFT)] = "keypad left",
    [(VC_KP_CLEAR) - (VC_KP_LEFT)] = "keypad clear",
    [(VC_KP_RIGHT) - (VC_KP_LEFT)] = "keypad right",
};

static const char *const vc_ee4f_ee53[] = {
    [(VC_KP_END)       - (VC_KP_END)] = "keypad end",
    [(VC_KP_DOWN)      - (VC_KP_END)] = "keypad down",
    [(VC_KP_PAGE_DOWN) - (VC_KP_END)] = "keypad page down",
    [(VC_KP_INSERT)    - (VC_KP_END)] = "keypad insert",
    [(VC_KP_DELETE)    - (VC_KP_END)] = "keypad delete",
};

static const char *const vc_ff74_ff7e[] = {
    [VC_SUN_OPEN   - VC_SUN_OPEN] = "Sun Open",
    [VC_SUN_HELP   - VC_SUN_OPEN] = "Sun Help",
    [VC_SUN_PROPS  - VC_SUN_OPEN] = "Sun Props",
    [VC_SUN_FRONT  - VC_SUN_OPEN] = "Sun Front",
    [VC_SUN_STOP   - VC_SUN_OPEN] = "Sun Stop",
    [VC_SUN_AGAIN  - VC_SUN_OPEN] = "Sun Again",
    [VC_SUN_UNDO   - VC_SUN_OPEN] = "Sun Undo",
    [VC_SUN_CUT    - VC_SUN_OPEN] = "Sun Cut",
    [VC_SUN_COPY   - VC_SUN_OPEN] = "Sun Copy",
    [VC_SUN_INSERT - VC_SUN_OPEN] = "Sun Insert",
    [VC_SUN_FIND   - VC_SUN_OPEN] = "Sun Find",
};

#define VC_RANGES_SIZE 37

static const struct vc_range vc_ranges[VC_RANGES_SIZE] = {
    { VC_UNDEFINED,       VC_SCROLL_LOCK,    vc_0000_0046 },
    { VC_KP_7,            VC_KP_SEPARATOR,   vc_0047_0053 },
    { VC_F11,             VC_F12,            vc_0057_0058 },
    { VC_F13,             VC_F15,            vc_005b_005d },
    { VC_F16,             VC_F24,            vc_0063_006b },
    { VC_KATAKANA,        VC_KATAKANA,       vc_0070 },
    { VC_UNDERSCORE,      VC_UNDERSCORE,     vc_0073 },
    { VC_FURIGANA,        VC_FURIGANA,       vc_0077 },
    { VC_KANJI,           VC_KANJI,          vc_0079 },
    { VC_HIRAGANA,        VC_HIRAGANA,       vc_007b },
    { VC_YEN,             VC_KP_COMMA,       vc_007d_007e },
    { VC_KP_EQUALS,       VC_KP_EQUALS,      vc_0e0d },
    { VC_KP_ENTER,        VC_CONTROL_R,      vc_0e1c_0e1d },
    { VC_KP_DIVIDE,       VC_KP_DIVIDE,      vc_0e35 },
    { VC_PRINTSCREEN,     VC_ALT_R,          vc_0e37_0e38 },
    { VC_PAUSE,           VC_HOME,           vc_0e45_0e47 },
    { VC_PAGE_UP,         VC_PAGE_UP,        vc_0e49 },
    { VC_END,             VC_END,            vc_0e4f },
    { VC_PAGE_DOWN,       VC_DELETE,         vc_0e51_0e53 },
    { VC_META_L,          VC_CONTEXT_MENU,   vc_0e5b_0e5d },
    { VC_MEDIA_PREVIOUS,  VC_MEDIA_PREVIOUS, vc_e010 },
    { VC_MEDIA_NEXT,      VC_MEDIA_NEXT,     vc_e019 },
    { VC_VOLUME_MUTE,     VC_MEDIA_STOP,     vc_e020_e024 },
    { VC_MEDIA_EJECT,     VC_MEDIA_EJECT,    vc_e02c },
    { VC_VOLUME_DOWN,     VC_VOLUME_DOWN,    vc_e02e },
    { VC_VOLUME_UP,       VC_BROWSER_HOME,   vc_e030_e032 },
    { VC_APP_MUSIC,       VC_APP_MUSIC,      vc_e03c },
    { VC_UP,              VC_UP,             vc_e048 },
    { VC_LEFT,            VC_RIGHT,          vc_e04b_e04d },
    { VC_DOWN,            VC_DOWN,           vc_e050 },
    { VC_POWER,           VC_SLEEP,          vc_e05e_e05f },
    { VC_WAKE,            VC_BROWSER_BACK,   vc_e063_e06a },
    { VC_APP_MAIL,        VC_MEDIA_SELECT,   vc_e06c_e06d },
    { VC_KP_HOME,         VC_KP_PAGE_UP,     vc_ee47_ee49 },
    { VC_KP_LEFT,         VC_KP_RIGHT,       vc_ee4b_ee4d },
    { VC_KP_END,          VC_KP_DELETE,      vc_ee4f_ee53 },
    { VC_SUN_OPEN,        VC_SUN_FIND,       vc_ff74_ff7e },
};

const char *keycode_to_name(uint16_t vc) {
    for (size_t i = 0; i < VC_RANGES_SIZE; ++i) {
        const struct vc_range *r = &vc_ranges[i];

        if (vc >= r->first && vc <= r->last) {
            return r->names[vc - r->first];
        }
    }

    return NULL;
}