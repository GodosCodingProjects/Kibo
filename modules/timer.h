
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

bool update_cooldown_timer(struct cooldown_timer* cdt)
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