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
#include "debug_led.h"
#include "delta_time.h"
#include "hardware/uart.h"
#include "input_parse.h"
#include "key_map.h"
#include "pico/stdlib.h"
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

#define KIBO_MASTER
#ifndef KIBO_MASTER
#define KIBO_PUPPET
#endif

#define UART_TX_PIN 0
#define UART_RX_PIN 1

const u32 key_send_cooldown = 4;
const u32 frame_delay = 1;

void init();
void send_hid_report_left(u32 gpio);
void send_hid_report_right(u32 gpio);
void send_uart(u32 gpio);
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
    debug_led_off();

    while (1)
    {
        tud_task();
        delta_time_update();

        parse_inputs();
        handle_events();

#ifdef KIBO_MASTER
        handle_uart();
#endif

        sleep_ms(frame_delay);
    }
}

void init()
{
    board_init();
    debug_led_init();

#ifdef KIBO_MASTER
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
        gp_on(get_gp_left(i));
    }

    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    if (board_init_after_tusb)
    {
        board_init_after_tusb();
    }
#else
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
        gp_on(get_gp_right(i));
    }
#endif

    // Set up our UART with the required speed.
    uart_init(uart0, 115200);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(uart0, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(uart0, UART_RX_PIN));
}

void send_hid_report_left(u32 i)
{
    if (*get_keycodes_left(i) == HID_KEY_LAYER_TOGGLE)
    {
        change_layer();
        return;
    }

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, get_keycodes_left(i));
    sleep_ms(key_send_cooldown);
    tud_task();

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    sleep_ms(key_send_cooldown);
    tud_task();
}

void send_hid_report_right(u32 i)
{
    if (*get_keycodes_right(i) == HID_KEY_LAYER_TOGGLE)
    {
        change_layer();
        return;
    }

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, get_keycodes_right(i));
    sleep_ms(key_send_cooldown);
    tud_task();

    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    sleep_ms(key_send_cooldown);
    tud_task();
}

void send_uart(u32 i)
{
    u8 output = (u8)i;
    uart_write_blocking(uart0, &output, 1);
}

void parse_inputs()
{
    for (u32 i = 0; i < GP_COUNT; ++i)
    {
#ifdef KIBO_MASTER
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
        if (input_down(i))
        {
            debug_led_on();

#ifdef KIBO_MASTER
            send_hid_report_left(i);
#else
            send_uart(i);
#endif
        }
        else if (input_up(i))
        {
            debug_led_off();
        }
    }
}

void handle_uart()
{
    if (uart_is_readable(uart0))
    {
        u8 i;
        uart_read_blocking(uart0, &i, 1);

        send_hid_report_right(i);
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
