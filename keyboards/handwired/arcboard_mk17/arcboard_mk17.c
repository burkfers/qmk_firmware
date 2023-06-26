// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk17.h"

////  QUANTUM PAINTER SECTION  ////
#if defined(QUANTUM_PAINTER_ENABLE)
    #include "qp_st7789.h"
    // #include <qp_lvgl.h>
    #include <qp.h>
    painter_device_t display;
    bool lcd_power = false;
    __attribute__((weak)) void draw_ui_user(void) {} //_user should not be in the keyboard.c
    __attribute__((weak)) void ui_init(void) {}
#endif

// clang-format off
    /* row,col
     * .------+------+------+------+------+------.                                                       .------+------+------+------+------+------.
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                                       |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                                                       |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |                                                       |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |                                                       |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |
     * '------+------+------+------+------+------+------+------+------.             .------+------+------+------+------+------+------+------+------'
     *        |  trackball  |  5,1 |  5,2 |------|  6,1 |  6,2 |  6,3 |             |  6,1 |  6,2 |  6,3 |------|  5,1 |  5,2 |  trackball  |
     *        '-------------+------+------+------+------+------+------'             +------+------+------+------+------+------+-------------'
     *                      |  5,3 |  5,4 |  5,5 |  6,3 |  6,4 |                    |  6,3 |  6,4 |             |  5,3 |  5,4 |  5,5 |
     *                      '------+------+------+------+------' .------.  .------. '------+------'             +------+------+------'
     *                             |  5,6 |          |  6,5 |    |  6,6 |  |  6,6 |     |  6,5 |                       |  5,6 |
     *                             '------'          '------'    '------'  '------'     '------'                       '------'
     * 5,1-5,6  = thumb keys
     * 6,1-6,4  = 5-way/dpad up/down/left/right
     * 6,5      = 5-way/dpad button
     * 6,6      = falcon button
     */
// clang-format on

/*
    LED chain is as follows:
    30x2 LEDs for the keys ((4x6 + 6) +2 sides), 12 LEDs for each falcon, 14 LEDs for each indicator strip
    Keys-L(0-29) -> Falcon-L(60-71) -> Indicators-L(84-97) -> Keys-R(30-59) -> Falcon-R(72-83) -> Indicators-R(98-111)
    Indicators can be further broken up into banks.
*/

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
led_config_t g_led_config = {
    // Key Matrix to LED Index - this is used to provide the 'default' white colour
    // This is just the keys leds, not falcon or indicators.
    //  24 + 5 + 12 + 12 + 11 = 64
    {
        { 0,  1,  2,  3,  4,  5  },         // Left, main
        { 6,  7,  8,  9,  10, 11 },         // Left, main
        { 12, 13, 14, 15, 16, 17 },         // Left, main
        { 18, 19, 20, 21, 22, 23 },         // Left, main
        { 24, 25, 26, 27, 28 },             // Left, thumb
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Left, dpad
        { 29, 30, 31, 32, 33, 34 },         // Left, Falcon1
        { 35, 36, 37, 38, 39, 40 },         // Left, Falcon1
        { 41, 42, 43, 44, 45, 46 },         // Left, Falcon2
        { 47, 48, 49, 50, 51, 52 },         // Left, Falcon2
        { 53, 54, 55, 56, 57, 58 },         // Left, indicator strip
        { 59, 60, 61, 62, 63  },            // Left, indicator strip

        { 64, 65, 66, 67, 68, 69 },         // Right, main
        { 70, 71, 72, 73, 74, 75 },         // Right, main
        { 76, 77, 78, 79, 80, 81 },         // Right, main
        { 82, 83, 84, 85, 86, 87 },         // Right, main
        { 88, 89, 90, 91, 92 },             // Right, thumb
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Right, dpad
        { 93, 94, 95, 96, 97, 98 },         // Right, Falcon1
        { 99, 100, 101, 102, 103, 104 },         // Right, Falcon1
        { 105, 106, 107, 108, 109, 110 },         // Right, Falcon2
        { 111, 112, 113, 114, 115, 116 },         // Right, Falcon2
        { 117, 118, 119, 120, 121, 122 },         // Right, indicator strip
        { 123, 124, 125, 126, 127 },              // Right, indicator strip
    },
    // LED Index to Physical Position
    // only used for animations, but necessary for qmk to compile
    // include every LED here
    // needs to match entire led chain, not just keys
    {
        { 102,   0 }, {  81,   0 }, {  61,   0 }, {  41,   0 }, {  20,   0 }, {   0,   0 },
        { 102,  16 }, {  81,  16 }, {  61,  16 }, {  41,  16 }, {  20,  16 }, {   0,  16 },
        { 102,  32 }, {  81,  32 }, {  61,  32 }, {  41,  32 }, {  20,  32 }, {   0,  32 },
        { 102,  48 }, {  81,  48 }, {  61,  48 }, {  41,  48 }, {  20,  48 }, {   0,  48 },
        { 224,   0 }, { 204,   0 }, { 183,   0 }, { 163,   0 }, { 143,   0 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 },
        { 224,  16 }, { 204,  16 }, { 183,  16 }, { 163,  16 }, { 143,  16 }, { 122,  16 },
        { 224,  32 }, { 204,  32 }, { 183,  32 }, { 163,  32 }, { 143,  32 }, { 122,  32 },
        { 224,  48 }, { 204,  48 }, { 183,  48 }, { 163,  48 }, { 143,  48 }, { 122,  48 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 },
    },
    // LED type bit mask - 4 is per-key
    // include every LED here
    // ordered by keys+thumbL, keys+thumbR, falconL, falconR, indicatorL, indicatorR
    // remember the 5-way/dpad has no LEDs, and occupies a row
    {
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    }
};
#endif

void keyboard_post_init_kb(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
        display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
        qp_init(display, QP_ROTATION_0);
        // qp_rect(display, 0, 0, 240, 320, HSV_BLACK, true);
        // print here
        wait_ms(50);
    #endif
    #if defined(POINTING_DEVICE_ENABLE)
        pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);
        pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    #endif
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

void housekeeping_task_kb(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
        // set the lcd_power state bool based on matrix activity vs. SCREEN_TIMEOUT value
        lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;
        setPinOutput(BACKLIGHT_PIN);
        if (lcd_power) {
            writePinHigh(BACKLIGHT_PIN);
            qp_power(display, true);
        } else {
            writePinLow(BACKLIGHT_PIN);
            qp_power(display, false);
        }

        if (lcd_power) {
            qp_rect(display, 0, 0, 240, 320, HSV_BLACK, true);
            // qp_rect(display, 0, 0, 240, 106, HSV_RED, true);
            // qp_rect(display, 0, 106, 240, 212, HSV_GREEN, true);
            // qp_rect(display, 0, 212, 240, 320, HSV_BLUE, true);
            qp_flush(display);
        }
    #endif // QUANTUM_PAINTER_ENABLE
}

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void matrix_slave_scan_keymap(void);
