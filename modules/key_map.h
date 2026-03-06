/*
 * MIT License
 *
 * Copyright (c) 2025 Godefroy Juteau
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef KEY_MAP_H
#define KEY_MAP_H

#include "bsp/board_api.h"
#include "events.h"
#include "tusb.h"
#include "types.h"

#include <stdbool.h>

#define GP_COUNT 20U

#define KEYS_PER_COMBO 6U
#define LAYER_COUNT 4U
#define HID_KEY_GOTO_LAYER 0xA5

static const u32 gp_map_left[GP_COUNT] = {
    2,  3,  4,  5,  6,  7,   // row 1
    8,  9,  10, 11, 12, 13,  // row 2
    14, 15, 16, 17, 18,      // row 3
    19, 20, 21               // thumb row
};

static const u32 gp_map_right[GP_COUNT] = {
    7,  2,  3,  4,  5,  6,   // row 1
    9,  10, 11, 8,  22, 21,  // row 2
    19, 20, 18, 17, 16,      // row 3
    15, 14, 13               // thumb row
};

static const u8 key_map_left[LAYER_COUNT][GP_COUNT][event_MAX - 1][KEYS_PER_COMBO] = {
    // Layer 0
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_2}, [event_DOWN] = {HID_KEY_BACKSPACE, HID_KEY_PERIOD, HID_KEY_C, HID_KEY_O, HID_KEY_M}},
     {[event_DOWN] = {HID_KEY_Q}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_Q}},
     {[event_DOWN] = {HID_KEY_W}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_W}},
     {[event_DOWN] = {HID_KEY_F}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_F}},
     {[event_DOWN] = {HID_KEY_P}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_P}},
     {[event_DOWN] = {HID_KEY_B}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_B}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_MINUS}, [event_PRESSED] = {HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH}},
     {[event_DOWN] = {HID_KEY_A}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_A}},
     {[event_DOWN] = {HID_KEY_R}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_R}},
     {[event_DOWN] = {HID_KEY_S}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_S}},
     {[event_DOWN] = {HID_KEY_T}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_T}},
     {[event_DOWN] = {HID_KEY_G}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_G}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_Z}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_Z}},
     {[event_DOWN] = {HID_KEY_X}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_X}},
     {[event_DOWN] = {HID_KEY_C}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_C}},
     {[event_DOWN] = {HID_KEY_D}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_D}},
     {[event_DOWN] = {HID_KEY_V}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_V}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_ENTER}},
     {[event_DOWN] = {HID_KEY_SPACE}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_MINUS}},
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 1}}
    },
    // Layer 1
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_ESCAPE}},
     {[event_DOWN] = {HID_KEY_BRACKET_LEFT, HID_KEY_A}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_BRACKET_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_A}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_3, HID_KEY_8}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_8, HID_KEY_3}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_K, HID_KEY_C}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_K, HID_KEY_U}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_TAB}},
     {[event_DOWN] = {HID_KEY_APOSTROPHE, HID_KEY_A}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_APOSTROPHE, HID_KEY_SHIFT_LEFT, HID_KEY_A}},
     {[event_DOWN] = {HID_KEY_APOSTROPHE, HID_KEY_D, HID_KEY_BACKSPACE}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_ALT_RIGHT, HID_KEY_CRSEL_PROPS}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_S}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_D}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_5}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_4}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_Z}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_Y}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_X}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_C}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_V}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_BACKSLASH, HID_KEY_N}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_BACKSLASH, HID_KEY_T}},
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 0}}
    },
    // Layer 2
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_ESCAPE}},
     {[event_DOWN] = {HID_KEY_O, HID_KEY_R}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_CRSEL_PROPS}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_3}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_8}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_BRACKET_LEFT, HID_KEY_D, HID_KEY_BACKSPACE}, [event_PRESSED] = {HID_KEY_EQUAL}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_CRSEL_PROPS}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_4}},
     {[event_DOWN] = {HID_KEY_A, HID_KEY_N, HID_KEY_D}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_7}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_MINUS}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_EQUAL}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_EQUAL}, [event_PRESSED] = {HID_KEY_EQUAL}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_N, HID_KEY_O, HID_KEY_T}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_1}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_5}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_BRACKET_LEFT, HID_KEY_D, HID_KEY_BACKSPACE}, [event_PRESSED] = {HID_KEY_EQUAL}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_SEMICOLON}, [event_PRESSED] = {HID_KEY_EQUAL}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_ENTER}},
     {[event_DOWN] = {HID_KEY_SPACE}},
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 0}}
    },
    // Layer 3
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_F1}},
     {[event_DOWN] = {HID_KEY_F2}},
     {[event_DOWN] = {HID_KEY_F3}},
     {[event_DOWN] = {HID_KEY_F4}},
     {[event_DOWN] = {HID_KEY_F5}},
     {[event_DOWN] = {HID_KEY_F6}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_ESCAPE}},
     {[event_DOWN] = {HID_KEY_M}},
     {[event_DOWN] = {HID_KEY_Q}},
     {[event_DOWN] = {HID_KEY_W}},
     {[event_DOWN] = {HID_KEY_E}},
     {[event_DOWN] = {HID_KEY_R}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT}},
     {[event_DOWN] = {HID_KEY_A}},
     {[event_DOWN] = {HID_KEY_S}},
     {[event_DOWN] = {HID_KEY_D}},
     {[event_DOWN] = {HID_KEY_B}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_ENTER}},
     {[event_DOWN] = {HID_KEY_SPACE}},
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 0}}
    }
};

static const u8 key_map_right[LAYER_COUNT][GP_COUNT][event_MAX - 1][KEYS_PER_COMBO] = {
    // Layer 0
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_J}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_J}},
     {[event_DOWN] = {HID_KEY_L}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_L}},
     {[event_DOWN] = {HID_KEY_U}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_U}},
     {[event_DOWN] = {HID_KEY_Y}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_Y}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_COMMA}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_2}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_9}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_0}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_M}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_M}},
     {[event_DOWN] = {HID_KEY_N}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_N}},
     {[event_DOWN] = {HID_KEY_E}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_E}},
     {[event_DOWN] = {HID_KEY_I}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_I}},
     {[event_DOWN] = {HID_KEY_O}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_O}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_LEFT}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_ALT_RIGHT, HID_KEY_BRACKET_RIGHT}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_K}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_K}},
     {[event_DOWN] = {HID_KEY_H}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_H}},
     {[event_DOWN] = {HID_KEY_COMMA}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SEMICOLON}},
     {[event_DOWN] = {HID_KEY_PERIOD}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_SEMICOLON}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_6}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_1}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 2}},
     {[event_DOWN] = {HID_KEY_BACKSPACE}},
     {[event_DOWN] = {HID_KEY_DELETE}}
    },
    // Layer 1
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_P}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_ALT_LEFT, HID_KEY_DELETE}},
     {[event_DOWN] = {HID_KEY_APOSTROPHE, HID_KEY_U}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_APOSTROPHE, HID_KEY_SHIFT_LEFT, HID_KEY_U}},
     {[event_DOWN] = {HID_KEY_BRACKET_LEFT, HID_KEY_I}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_BRACKET_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_I}},
     {[event_DOWN] = {HID_KEY_BRACKET_RIGHT, HID_KEY_C}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_BRACKET_RIGHT, HID_KEY_SHIFT_LEFT, HID_KEY_C}},
     {[event_DOWN] = {HID_KEY_BACKSLASH}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_F}},
     {[event_DOWN] = {HID_KEY_BRACKET_LEFT, HID_KEY_E}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_BRACKET_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_E}},
     {[event_DOWN] = {HID_KEY_SLASH}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_SLASH}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_APOSTROPHE}, [event_PRESSED] = {HID_KEY_I}},
     {[event_DOWN] = {HID_KEY_BRACKET_LEFT, HID_KEY_O}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_BRACKET_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_O}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_5}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_ALT_RIGHT, HID_KEY_BACKSLASH}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_G}},
     {[event_DOWN] = {HID_KEY_APOSTROPHE, HID_KEY_E}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_APOSTROPHE, HID_KEY_SHIFT_LEFT, HID_KEY_E}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_APOSTROPHE}, [event_PRESSED] = {HID_KEY_E}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_7}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_8}},
     {[event_DOWN] = {HID_KEY_CONTROL_LEFT, HID_KEY_SHIFT_LEFT, HID_KEY_ESCAPE}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_BACKSPACE}},
     {[event_DOWN] = {HID_KEY_DELETE}},
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 2}}
    },
    // Layer 2
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_0, HID_KEY_X}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_0, HID_KEY_B}},
     {[event_DOWN] = {HID_KEY_1}},
     {[event_DOWN] = {HID_KEY_2}},
     {[event_DOWN] = {HID_KEY_3}},
     {[event_DOWN] = {HID_KEY_BACKSLASH}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_BACKSLASH}},
     {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_9}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_0}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_F}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_PERIOD, HID_KEY_0, HID_KEY_F}},
     {[event_DOWN] = {HID_KEY_4}},
     {[event_DOWN] = {HID_KEY_5}},
     {[event_DOWN] = {HID_KEY_6}},
     {[event_DOWN] = {HID_KEY_0}},
     {[event_DOWN] = {HID_KEY_ALT_RIGHT, HID_KEY_APOSTROPHE}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_ALT_RIGHT, HID_KEY_BACKSLASH}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_L}, [event_PRESSED] = {HID_KEY_BACKSPACE, HID_KEY_SHIFT_LEFT, HID_KEY_U, HID_KEY_L}},
     {[event_DOWN] = {HID_KEY_7}},
     {[event_DOWN] = {HID_KEY_8}},
     {[event_DOWN] = {HID_KEY_9}},
     {[event_DOWN] = {HID_KEY_COMMA}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 3}},
     {[event_DOWN] = {HID_KEY_BACKSPACE}},
     {[event_DOWN] = {HID_KEY_PERIOD}}
    },
    // Layer 3
    {// Row 1 (top)
     {[event_DOWN] = {HID_KEY_F7}},
     {[event_DOWN] = {HID_KEY_F8}},
     {[event_DOWN] = {HID_KEY_F9}},
     {[event_DOWN] = {HID_KEY_F10}},
     {[event_DOWN] = {HID_KEY_F11}},
     {[event_DOWN] = {HID_KEY_F12}},
     // Row 2 (middle)
     {[event_DOWN] = {HID_KEY_O}},
     {[event_DOWN] = {HID_KEY_P}},
     {[event_DOWN] = {HID_KEY_ARROW_UP}},
     {[event_DOWN] = {HID_KEY_Z}},
     {[event_DOWN] = {HID_KEY_X}},
     {[event_DOWN] = {HID_KEY_C}},
     // Row 3 (bottom)
     {[event_DOWN] = {HID_KEY_K}},
     {[event_DOWN] = {HID_KEY_ARROW_LEFT}},
     {[event_DOWN] = {HID_KEY_ARROW_DOWN}},
     {[event_DOWN] = {HID_KEY_ARROW_RIGHT}},
     {[event_DOWN] = {HID_KEY_V}},
     // Row 4 (thumb)
     {[event_DOWN] = {HID_KEY_GOTO_LAYER, 2}},
     {[event_DOWN] = {HID_KEY_BACKSPACE}},
     {[event_DOWN] = {HID_KEY_DELETE}}
    }
};

static u32 cur_layer = 0;

const u32 get_gp_left(u32 i) { return gp_map_left[i]; }
const u32 get_gp_right(u32 i) { return gp_map_right[i]; }

const u8* get_keycodes_left(u32 i, key_events event) { return key_map_left[cur_layer][i][event]; }
const u8* get_keycodes_right(u32 i, key_events event) { return key_map_right[cur_layer][i][event]; }

void change_layer(u32 i) { cur_layer = i; }

#endif  // KEY_MAP_H