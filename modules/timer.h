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

#ifndef TIMER_H
#define TIMER_H

#include "bsp/board.h"
#include "types.h"

#include <stdbool.h>

struct cooldown_timer
{
    u32 cooldown;
    u32 last_update;
};

static u32 last_update = 0;

bool cooldown_timer_update(struct cooldown_timer* cdt)
{
    if (cdt->cooldown == 0)
    {
        return false;
    }

    if (cdt->last_update + cdt->cooldown > board_millis())
    {
        return false;
    }

    cdt->last_update += cdt->cooldown;
    return true;
}

#endif  // TIMER_H