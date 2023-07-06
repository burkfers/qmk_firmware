/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rgb_ledmaps.h"
#include "arcboard_mk17_tft.h"
#include "lib/lib8tion/lib8tion.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #include "keymap.h"
#endif

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }

void set_rgb_range(uint8_t led_min, uint8_t led_max, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    for (int i = led_min; i <= led_max; i++) {
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
        // hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
// bool BREATHING(effect_params_t* params) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//
//     HSV      hsv  = rgb_matrix_config.hsv;
//     uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
//     hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
//     RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return rgb_matrix_check_finished_leds(led_max);
// }

void set_rgb_led(int index, int hue, int sat, int val) {
    HSV hsv = {
        .h = hue,
        .s = sat,
        .v = 150,
    };
    // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    // hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    if (hsv.h || hsv.s) {
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
    }
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    set_rgb_range(led_min, led_max, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
