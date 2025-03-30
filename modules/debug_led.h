
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