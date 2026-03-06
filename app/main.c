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

//-------------------------------------------------------------------------------------------------+
// References frequently consulted
//-------------------------------------------------------------------------------------------------+

// https://github.com/hathach/tinyusb/blob/master/src/class/hid/hid.h
// https://unicode.org/charts/

//-------------------------------------------------------------------------------------------------+
// Includes
//-------------------------------------------------------------------------------------------------+

#include "bsp/board_api.h"
#include "class/hid/hid.h"
#include "debug_led.h"
#include "delta_time.h"
#include "hardware/uart.h"
#include "input_parse.h"
#include "key_map.h"
#include "pico/stdlib.h"
#include "pin_helper.h"
#include "tusb.h"
#include "tusb_config.h"
#include "types.h"
#include "usb_descriptors.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------+
// Constants and declarations
//-------------------------------------------------------------------------------------------------+

// #define KIBO_LEFT <- Now defined (or not) using build parameters

#define UART_TX_PIN 0
#define UART_RX_PIN 1

const u32 key_send_cooldown = 4;
const u32 frame_delay = 1;

bool is_master = true;

void init();
void send_hid_report(const u8* keycodes);
void send_uart(const u8 key, const key_events event);
void parse_inputs();
void handle_events();
void handle_uart();

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

    while (1)
    {
        tud_task();
        delta_time_update();

        parse_inputs();
        handle_events();
        if (is_master)
        {
            handle_uart();
        }

        sleep_ms(frame_delay);
    }
}

void init()
{
    board_init();
    debug_led_init();

    for (u32 i = 0; i < GP_COUNT; ++i)
    {
#ifdef KIBO_LEFT
        gp_on(get_gp_left(i));
#else
        gp_on(get_gp_right(i));
#endif
    }

    // init device stack on configured roothub port
    is_master = gp_get(PICO_VBUS_PIN);
    if (is_master)
    {
        tud_init(BOARD_TUD_RHPORT);
        // debug_led_on();
        debug_led_off();
    }
    else
    {
        debug_led_off();
    }

    if (board_init_after_tusb)
    {
        board_init_after_tusb();
    }

    // Set up our UART with the required speed.
    uart_init(uart0, 115200);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void send_hid_report(const u8* keycodes)
{
    if (keycodes[0] == HID_KEY_NONE)
    {
        return;
    }

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycodes);
    sleep_ms(key_send_cooldown);
    tud_task();

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    sleep_ms(key_send_cooldown);
    tud_task();
}

void send_uart(const u8 key, const key_events event)
{
    if (uart_is_writable(uart0))
    {
        u8 key_event[6] = {key, event};
        uart_write_blocking(uart0, key_event, 6);
    }
}

void parse_inputs()
{
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
#ifdef KIBO_LEFT
        update_input(i, gp_get(get_gp_left(i)));
#else
        update_input(i, gp_get(get_gp_right(i)));
#endif
    }
}

void handle_events()
{
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
        key_events event = get_event(i);
        if (event != event_RELEASED)
        {
#ifdef KIBO_LEFT
            const u8* keycodes = get_keycodes_left(i, event);
#else
            const u8* keycodes = get_keycodes_right(i, event);
#endif
            if (keycodes[0] == HID_KEY_NONE)
            {
                continue;
            }

            if (is_master)
            {
                // If it's a layer change, handle it internally
                if (keycodes[0] == HID_KEY_GOTO_LAYER)
                {
                    change_layer(keycodes[1]);
                    continue;
                }

                // Send actual keycodes to the computer via USB
                send_hid_report(keycodes);
            }
            else
            {
                // Send them to the master half
                send_uart(i, event);
            }
        }
    }
}

void handle_uart()
{
    if (uart_is_readable(uart0))
    {
        // Get the bytes from the uart
        static u8 key_info[6];
        uart_read_blocking(uart0, key_info, 6);

        // // Ignore if nothing to read
        // if (key_info[0] == HID_KEY_NONE)
        // {
        //     return;
        // }

        // Received keycodes come from the other keyboard half
#ifdef KIBO_LEFT
        const u8* keycodes = get_keycodes_right(key_info[0], key_info[1]);
#else
        const u8* keycodes = get_keycodes_left(key_info[0], key_info[1]);
#endif

        debug_led_on();

        // If it's a layer change, handle it internally
        if (keycodes[0] == HID_KEY_GOTO_LAYER)
        {
            change_layer(keycodes[1]);
            return;
        }

        // For actual keycodes, send them to the computer via USB
        send_hid_report(keycodes);
    }
}

//-------------------------------------------------------------------------------------------------+
// TinyUSB HID callbacks
//-------------------------------------------------------------------------------------------------+

// Callback: report sent successfully
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len) {}

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
void tud_umount_cb(void) {}

// Callback: connection suspended
void tud_suspend_cb(bool remote_wakeup_en)
{
    // Automatically resume the connection
    tud_remote_wakeup();
}

// Callback: connection resumed
void tud_resume_cb(void) {}
