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

#ifndef PIN_HELPER_H
#define PIN_HELPER_H

#include "pico/stdlib.h"
#include "types.h"

#include <stdbool.h>

void gp_in(u32 gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
}

void gp_out(u32 gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}

void gps_in(u32 gpio_0, u32 n_gpio)
{
    for (u32 i = 0; i < n_gpio; ++i)
    {
        gp_in(gpio_0 + i);
    }
}

void gps_out(u32 gpio_0, u32 n_gpio)
{
    for (u32 i = 0; i < n_gpio; ++i)
    {
        gp_out(gpio_0 + i);
    }
}

void gp_on(u32 gpio) { gpio_put(gpio, true); }

void gp_off(u32 gpio) { gpio_put(gpio, false); }

bool gp_get(u32 gpio) { return gpio_get(gpio); }

#endif  // PIN_HELPER_H