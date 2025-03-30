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

#ifndef DEBUG_LED_H
#define DEBUG_LED_H

#include "pico/stdlib.h"
#include "pin_helper.h"
#include "timer.h"
#include "types.h"

static struct cooldown_timer debug_led_cdt;

void debug_led_set_interval(u32 interval) { debug_led_cdt.cooldown = interval; }

void debug_led_init()
{
    gp_out(25);
    gpio_put(25, true);
    debug_led_set_interval(0);
}

void debug_led_update()
{
    static bool led_state = true;

    // blink is disabled
    if (!update_cooldown_timer(&debug_led_cdt))
    {
        return;
    }

    // toggle
    gpio_put(25, 1 - gp_get(25));
}

#endif  // DEBUG_LED_H