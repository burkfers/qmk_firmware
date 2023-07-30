// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcpedals_mk1.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #include "keymap.h"
#endif

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }

void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    for (int i = first_led; i <= last_led; i++) {
        // RGB_TOT_IND_L is 'how many right indicator leds between left and right key ranges, in the context of the led-flag section of g_led_config'
        // cuz, ledmaps doesn't think there are any indicator leds, it believes you only have l.key-range + r.key-range = total addressable leds
        if (!(is_keyboard_left())) {
            i = i - RGB_TOT_IND_L;
        }
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        if (!(is_keyboard_left())) {
            i = i + RGB_TOT_IND_L;
        } // revert i to fit the 'in reality' led sequence
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

// set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L0);
void set_rgb_range(uint8_t first_led, uint8_t last_led, int hue, int sat, int val) {
    for (int i = first_led; i <= last_led; i++) {
        HSV hsv = {
            .h = hue,
            .s = sat,
            .v = RGB_INDICATOR_BRIGHTNESS,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

static uint8_t layerIndicatorLeds[]         = {12,25,26,39,40,53};
static uint8_t leftOneIndicatorLeds[]       = {13,14,27,28,41,42};
static uint8_t leftTwoIndicatorLeds[]       = {15,16,29,30,43,44};
static uint8_t leftThreeIndicatorLeds[]     = {17,18,31,32,45,46};
static uint8_t rightOneIndicatorLeds[]      = {19,20,33,34,47,48};
static uint8_t rightTwoIndicatorLeds[]      = {21,22,35,36,49,50};
static uint8_t rightThreeIndicatorLeds[]    = {23,24,37,38,51,52};

// set_rgb_list(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L0);
void set_rgb_array(uint8_t ledArray[], int hue, int sat, int val, int layer) {
    // const ledmap *l = &(ledmaps[layer]);
    for (int i = 0; i <= 5; i++) {
        HSV hsv = {
            .h = hue,
            .s = sat,
            .v = RGB_INDICATOR_BRIGHTNESS,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(ledArray[i], rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
        set_rgb_array(layerIndicatorLeds, HSV_GREEN);
        set_rgb_array(leftOneIndicatorLeds, HSV_YELLOW);
        set_rgb_array(leftTwoIndicatorLeds, HSV_ORANGE);
        set_rgb_array(leftThreeIndicatorLeds, HSV_RED);
        set_rgb_array(rightOneIndicatorLeds, HSV_CYAN);
        set_rgb_array(rightTwoIndicatorLeds, HSV_SPRINGGREEN);
        set_rgb_array(rightThreeIndicatorLeds, HSV_GREEN);
    }
    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
