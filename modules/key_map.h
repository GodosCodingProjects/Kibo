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
#include "tusb.h"
#include "types.h"

#include <stdbool.h>

#define GP0 2U
#define GP_COUNT 20U
#define KEYS_PER_COMBO 6U

#define LAYER_COUNT 2U

#define HID_KEY_LAYER_TOGGLE 0xA5

static u32 cur_layer = 0;

static const u8 key_map_left[LAYER_COUNT][GP_COUNT][KEYS_PER_COMBO] = {
    // Layer 0
    {
        // Row 1 (top)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_Q},
        {HID_KEY_W},
        {HID_KEY_F},
        {HID_KEY_P},
        {HID_KEY_B},
        // Row 2 (middle)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_A},
        {HID_KEY_R},
        {HID_KEY_S},
        {HID_KEY_T},
        {HID_KEY_G},
        // Row 3 (bottom)
        {HID_KEY_Z},
        {HID_KEY_X},
        {HID_KEY_C},
        {HID_KEY_D},
        {HID_KEY_V},
        // Row 4 (thumb)
        {HID_KEY_BACKSPACE},
        {HID_KEY_SPACE},
        {HID_KEY_ENTER},
    },
    // Layer 1
    {
        // Row 1 (top)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_SHIFT_LEFT, HID_KEY_Q},
        {HID_KEY_SHIFT_LEFT, HID_KEY_W},
        {HID_KEY_SHIFT_LEFT, HID_KEY_F},
        {HID_KEY_SHIFT_LEFT, HID_KEY_P},
        {HID_KEY_SHIFT_LEFT, HID_KEY_B},
        // Row 2 (middle)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_SHIFT_LEFT, HID_KEY_A},
        {HID_KEY_SHIFT_LEFT, HID_KEY_R},
        {HID_KEY_SHIFT_LEFT, HID_KEY_S},
        {HID_KEY_SHIFT_LEFT, HID_KEY_T},
        {HID_KEY_SHIFT_LEFT, HID_KEY_G},
        // Row 3 (bottom)
        {HID_KEY_SHIFT_LEFT, HID_KEY_Z},
        {HID_KEY_SHIFT_LEFT, HID_KEY_X},
        {HID_KEY_SHIFT_LEFT, HID_KEY_C},
        {HID_KEY_SHIFT_LEFT, HID_KEY_D},
        {HID_KEY_SHIFT_LEFT, HID_KEY_V},
        // Row 4 (thumb)
        {HID_KEY_BACKSPACE},
        {HID_KEY_SPACE},
        {HID_KEY_ENTER},
    }
};

static const u8 key_map_right[LAYER_COUNT][GP_COUNT][KEYS_PER_COMBO] = {
    // Layer 0
    {
        // Row 1 (top)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_Q},
        {HID_KEY_W},
        {HID_KEY_F},
        {HID_KEY_P},
        {HID_KEY_B},
        // Row 2 (middle)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_N},
        {HID_KEY_E},
        {HID_KEY_I},
        {HID_KEY_O},
        {HID_KEY_G},
        // Row 3 (bottom)
        {HID_KEY_Z},
        {HID_KEY_X},
        {HID_KEY_C},
        {HID_KEY_D},
        {HID_KEY_V},
        // Row 4 (thumb)
        {HID_KEY_BACKSPACE},
        {HID_KEY_SPACE},
        {HID_KEY_ENTER},
    },
    // Layer 1
    {
        // Row 1 (top)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_SHIFT_LEFT, HID_KEY_Q},
        {HID_KEY_SHIFT_LEFT, HID_KEY_W},
        {HID_KEY_SHIFT_LEFT, HID_KEY_F},
        {HID_KEY_SHIFT_LEFT, HID_KEY_P},
        {HID_KEY_SHIFT_LEFT, HID_KEY_B},
        // Row 2 (middle)
        {HID_KEY_LAYER_TOGGLE},
        {HID_KEY_SHIFT_LEFT, HID_KEY_N},
        {HID_KEY_SHIFT_LEFT, HID_KEY_E},
        {HID_KEY_SHIFT_LEFT, HID_KEY_I},
        {HID_KEY_SHIFT_LEFT, HID_KEY_O},
        {HID_KEY_SHIFT_LEFT, HID_KEY_G},
        // Row 3 (bottom)
        {HID_KEY_SHIFT_LEFT, HID_KEY_Z},
        {HID_KEY_SHIFT_LEFT, HID_KEY_X},
        {HID_KEY_SHIFT_LEFT, HID_KEY_C},
        {HID_KEY_SHIFT_LEFT, HID_KEY_D},
        {HID_KEY_SHIFT_LEFT, HID_KEY_V},
        // Row 4 (thumb)
        {HID_KEY_BACKSPACE},
        {HID_KEY_SPACE},
        {HID_KEY_ENTER},
    }
};

const u8* get_keycodes_left(u32 gpio) { return key_map_left[cur_layer][gpio - GP0]; }
const u8* get_keycodes_right(u32 gpio) { return key_map_right[cur_layer][gpio - GP0]; }

void change_layer() { cur_layer = 1 - cur_layer; }  // Toggle for now

#endif  // KEY_MAP_H