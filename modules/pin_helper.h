
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