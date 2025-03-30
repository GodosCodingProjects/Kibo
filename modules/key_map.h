
#ifndef KEY_MAP_H
#define KEY_MAP_H

#include "bsp/board_api.h"
#include "tusb.h"
#include "types.h"

#include <stdbool.h>

#define GP0 2U
#define GP_COUNT 20U

static const u8 key_map[] = {
    // Row 1 (top)
    HID_KEY_CONTROL_LEFT,
    HID_KEY_Q,
    HID_KEY_W,
    HID_KEY_F,
    HID_KEY_P,
    HID_KEY_B,
    // Row 2 (middle)
    HID_KEY_SHIFT_LEFT,
    HID_KEY_A,
    HID_KEY_R,
    HID_KEY_S,
    HID_KEY_T,
    HID_KEY_G,
    // Row 3 (bottom)
    HID_KEY_Z,
    HID_KEY_X,
    HID_KEY_C,
    HID_KEY_D,
    HID_KEY_V,
    // Row 4 (thumb)
    HID_KEY_BACKSPACE,
    HID_KEY_SPACE,
    HID_KEY_ENTER,
};

void get_keycodes(u32 gpio, /*out*/ u8 keycodes[6]) { keycodes[0] = key_map[gpio - GP0]; }

#endif  // KEY_MAP_H