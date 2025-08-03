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
#define LAYER_COUNT 2U
#define HID_KEY_LAYER_TOGGLE 0xA5

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
    {
        // Row 1 (top)
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        {[event_UP] = {HID_KEY_Q}},
        {[event_UP] = {HID_KEY_W}},
        {[event_UP] = {HID_KEY_F}},
        {[event_UP] = {HID_KEY_P}},
        {[event_UP] = {HID_KEY_B}},
        // Row 2 (middle)
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        {[event_DOWN] = {HID_KEY_A}},
        {[event_DOWN] = {HID_KEY_R}},
        {[event_DOWN] = {HID_KEY_S}},
        {[event_DOWN] = {HID_KEY_T}},
        {[event_DOWN] = {HID_KEY_G}},
        // Row 3 (bottom)
        {[event_DOWN] = {HID_KEY_Z}},
        {[event_DOWN] = {HID_KEY_X}},
        {[event_DOWN] = {HID_KEY_C}},
        {[event_DOWN] = {HID_KEY_D}},
        {[event_DOWN] = {HID_KEY_V}},
        // Row 4 (thumb)
        {[event_DOWN] = {HID_KEY_BACKSPACE}},
        {[event_DOWN] = {HID_KEY_SPACE}},
        {[event_DOWN] = {HID_KEY_ENTER}},
    },
    // Layer 1
    {
        // Row 1 (top)
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_Q}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_W}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_F}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_P}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_B}},
        // Row 2 (middle)
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_A}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_R}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_S}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_T}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_G}},
        // Row 3 (bottom)
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_Z}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_X}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_C}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_D}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_V}},
        // Row 4 (thumb)
        {[event_DOWN] = {HID_KEY_BACKSPACE}},
        {[event_DOWN] = {HID_KEY_SPACE}},
        {[event_DOWN] = {HID_KEY_ENTER}},
    }
};

static const u8 key_map_right[LAYER_COUNT][GP_COUNT][event_MAX - 1][KEYS_PER_COMBO] = {
    // Layer 0
    {
        // Row 1 (top)
        {[event_DOWN] = {HID_KEY_J}},
        {[event_DOWN] = {HID_KEY_L}},
        {[event_DOWN] = {HID_KEY_U}},
        {[event_DOWN] = {HID_KEY_Y}},
        {[event_DOWN] = {HID_KEY_SEMICOLON}},
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        // Row 2 (middle)
        {[event_DOWN] = {HID_KEY_M}},
        {[event_DOWN] = {HID_KEY_N}},
        {[event_DOWN] = {HID_KEY_E}},
        {[event_DOWN] = {HID_KEY_I}},
        {[event_DOWN] = {HID_KEY_O}},
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        // Row 3 (bottom)
        {[event_DOWN] = {HID_KEY_K}},
        {[event_DOWN] = {HID_KEY_H}},
        {[event_DOWN] = {HID_KEY_COMMA}},
        {[event_DOWN] = {HID_KEY_PERIOD}},
        {[event_DOWN] = {HID_KEY_SLASH}},
        // Row 4 (thumb)
        {[event_DOWN] = {HID_KEY_BACKSPACE}},
        {[event_DOWN] = {HID_KEY_SPACE}},
        {[event_DOWN] = {HID_KEY_ENTER}},
    },
    // Layer 1
    {
        // Row 1 (top)
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_J}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_L}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_U}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_Y}},
        {[event_DOWN] = {HID_KEY_SEMICOLON}},
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        // Row 2 (middle)
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_M}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_N}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_E}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_I}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_O}},
        {[event_DOWN] = {HID_KEY_LAYER_TOGGLE}},
        // Row 3 (bottom)
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_K}},
        {[event_DOWN] = {HID_KEY_SHIFT_LEFT, HID_KEY_H}},
        {[event_DOWN] = {HID_KEY_COMMA}},
        {[event_DOWN] = {HID_KEY_PERIOD}},
        {[event_DOWN] = {HID_KEY_SLASH}},
        // Row 4 (thumb)
        {[event_DOWN] = {HID_KEY_BACKSPACE}},
        {[event_DOWN] = {HID_KEY_SPACE}},
        {[event_DOWN] = {HID_KEY_ENTER}},
    }
};

static u32 cur_layer = 0;

const u32 get_gp_left(u32 i) { return gp_map_left[i]; }
const u32 get_gp_right(u32 i) { return gp_map_right[i]; }

const u8* get_keycodes_left(u32 i, key_events event) { return key_map_left[cur_layer][i][event]; }
const u8* get_keycodes_right(u32 i, key_events event) { return key_map_right[cur_layer][i][event]; }

void change_layer() { cur_layer = 1 - cur_layer; }  // Toggle for now

#endif  // KEY_MAP_H