// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk17_tft.h"
#include "qp_st7789.h"
#include <qp.h>
#include <color.h>
#include "print.h"

////  QUANTUM PAINTER SECTION  ////
#if defined(QUANTUM_PAINTER_ENABLE)
    #include "qp_st7789.h"
    #include <qp.h>
    __attribute__((weak)) void draw_ui_user(void) {}
    __attribute__((weak)) void init_ui(void) {}
    extern painter_device_t display;
#endif

void keyboard_post_init_kb(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
        init_ui();
    #endif
    #if defined(POINTING_DEVICE_ENABLE)
        pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);
        pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    #endif
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
led_config_t g_ledmap_config = {
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

// trying to shrink to match matrix
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
        { 24, 25, 26, 27, 28, NO_LED },             // Left, thumb, NO_LED for falcon1 button
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Left, NO_LED for dpad, falcon2 button
        { 29, 30, 31, 32, 33, 34 },         // Right, main
        { 35, 36, 37, 38, 39, 40 },         // Right, main
        { 41, 42, 43, 44, 45, 46 },         // Right, main
        { 47, 48, 49, 50, 51, 52 },         // Right, main
        { 53, 54, 55, 56, 57, NO_LED },     // Right, thumb, NO_LED for falcon1 button
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Right, dpad, falcon2 button
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
        { 224,  16 }, { 204,  16 }, { 183,  16 }, { 163,  16 }, { 143,  16 }, { 122,  16 },
        { 224,  32 }, { 204,  32 }, { 183,  32 }, { 163,  32 }, { 143,  32 }, { 122,  32 },
        { 224,  48 }, { 204,  48 }, { 183,  48 }, { 163,  48 }, { 143,  48 }, { 122,  48 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 },
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
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
    }
};
#endif
