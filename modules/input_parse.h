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

#ifndef INPUT_PARSE_H
#define INPUT_PARSE_H

#include "delta_time.h"
#include "key_map.h"
#include "types.h"

#include <stdbool.h>

static u32 key_inputs[GP_COUNT] = {0};
static const u32 ms_to_released = 0;
static const u32 ms_to_up = 10;
static const u32 ms_to_down = 20;
static const u32 ms_to_pressed = 30;

enum key_events
{
    event_RELEASED,  // Release held
    event_UP,        // Release detected
    event_DOWN,      // Press detected
    event_PRESSED,   // Press held
    event_MAX,
};
struct event
{
    enum key_events event;
    bool was_consumed;
};
static struct event last_key_events[GP_COUNT];

static void update_event(u32 i)
{
    if (last_key_events[i].event != event_DOWN && last_key_events[i].event != event_PRESSED &&
        key_inputs[i] == ms_to_down)
    {
        last_key_events[i].event = event_DOWN;
        last_key_events[i].was_consumed = false;
    }
    else if (last_key_events[i].event == event_DOWN && key_inputs[i] == ms_to_pressed)
    {
        last_key_events[i].event = event_PRESSED;
        last_key_events[i].was_consumed = false;
    }
    else if (last_key_events[i].event != event_UP && last_key_events[i].event != event_RELEASED &&
             key_inputs[i] == ms_to_up)
    {
        last_key_events[i].event = event_UP;
        last_key_events[i].was_consumed = false;
    }
    else if (last_key_events[i].event == event_UP && key_inputs[i] == ms_to_released)
    {
        last_key_events[i].event = event_RELEASED;
        last_key_events[i].was_consumed = false;
    }
}

void update_input(u32 i, bool is_pressed)
{
    if (is_pressed)
    {
        if (key_inputs[i] < ms_to_pressed)
        {
            key_inputs[i] += delta_time();

            if (key_inputs[i] > ms_to_pressed)
            {
                key_inputs[i] = ms_to_pressed;
            }
        }
    }
    else
    {
        if (key_inputs[i] > ms_to_released)
        {
            if (delta_time() > key_inputs[i])
            {
                key_inputs[i] = 0;
            }
            else
            {
                key_inputs[i] -= delta_time();
            }
        }
    }

    update_event(i);
}

bool input_down(u32 i)
{
    if (last_key_events[i].event == event_DOWN && !last_key_events[i].was_consumed)
    {
        last_key_events[i].was_consumed = true;
        return true;
    }

    return false;
}
bool input_pressed(u32 i) { return (last_key_events[i].event == event_PRESSED); }

bool input_up(u32 i)
{
    if (last_key_events[i].event == event_UP && !last_key_events[i].was_consumed)
    {
        last_key_events[i].was_consumed = true;
        return true;
    }

    return false;
}
bool input_released(u32 i) { return (last_key_events[i].event == event_RELEASED); }

#endif  // INPUT_PARSE_H