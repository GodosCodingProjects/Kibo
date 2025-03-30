
//-------------------------------------------------------------------------------------------------+
// References frequently consulted
//-------------------------------------------------------------------------------------------------+

// https://github.com/hathach/tinyusb/blob/master/src/class/hid/hid.h
// https://unicode.org/charts/

//-------------------------------------------------------------------------------------------------+
// Includes
//-------------------------------------------------------------------------------------------------+

#include "bsp/board_api.h"
#include "debug_led.h"
#include "input_parse.h"
#include "key_map.h"
#include "pin_helper.h"
#include "tusb.h"
#include "types.h"
#include "usb_descriptors.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------+
// Constants and declarations
//-------------------------------------------------------------------------------------------------+

enum
{
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500,
};

void hid_task(void);

bool lastCallbackWasEmpty = false;

const u32 key_send_cooldown = 4;
const u32 frame_delay = 1;

void init();
void send_hid_report(u32 gpio);
void parse_inputs();
void handle_events();

//-------------------------------------------------------------------------------------------------+
// Main
//-------------------------------------------------------------------------------------------------+

/*
 *      Notes:
 *      You need to call tud_task() before every call to tud_hid_keyboard_report()
 *      You need to wait at least 4 ms before flushing the keys.
 */

int main(void)
{
    init();
    gp_off(25);

    while (1)
    {
        // debug_led_update();
        tud_task();

        parse_inputs();

        handle_events();

        sleep_ms(frame_delay);
    }
}

void init()
{
    board_init();
    debug_led_init();
    gps_in(GP0, GP_COUNT);

    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    if (board_init_after_tusb)
    {
        board_init_after_tusb();
    }
}

void send_hid_report(u32 gpio)
{
    u8 keycodes[6] = {0};
    get_keycodes(gpio, keycodes);

    // Debug
    gp_on(25);

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycodes);
    sleep_ms(key_send_cooldown);
    tud_task();

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    sleep_ms(key_send_cooldown);
    tud_task();
}

void parse_inputs()
{
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
        update_input(i, gp_get(i + GP0));
    }
}

void handle_events()
{
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
        if (input_down(i))
        {
            send_hid_report(i + GP0);
        }
    }
}

//-------------------------------------------------------------------------------------------------+
// TinyUSB HID callbacks
//-------------------------------------------------------------------------------------------------+

// Callback: report sent successfully
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
    // if (!lastCallbackWasEmpty)
    // {
    //     // send empty key report if previously has key pressed
    //     tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    //     lastCallbackWasEmpty = true;
    // }
}

// Callback: received get_report control request
uint16_t tud_hid_get_report_cb(
    uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer,
    uint16_t reqlen
)
{
    return 0;
}

// Callback: received set_report control request
void tud_hid_set_report_cb(
    uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer,
    uint16_t bufsize
)
{
}

//-------------------------------------------------------------------------------------------------+
// Device callbacks
//-------------------------------------------------------------------------------------------------+

// Callback: device mounted successfully
void tud_mount_cb(void) {}

// Callback: device unmounted successfully
void tud_umount_cb(void) { debug_led_set_interval(BLINK_NOT_MOUNTED); }

// Callback: connection suspended
void tud_suspend_cb(bool remote_wakeup_en)
{
    // Automatically resume the connection
    tud_remote_wakeup();
}

// Callback: connection resumed
void tud_resume_cb(void) {}
