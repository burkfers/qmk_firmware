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
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
        { 0 },
    },
    // LED Index to Physical Position
    // only used for animations, but necessary for qmk to compile
    // include every LED here
    // needs to match entire led chain, not just keys
    {
        { 0,   0 }
    },
    // LED type bit mask - 4 is per-key
    // include every LED here
    // ordered by keys+thumbL, keys+thumbR, falconL, falconR, indicatorL, indicatorR
    // remember the 5-way/dpad has no LEDs, and occupies a row
    {
            4,
    }
};
#endif
