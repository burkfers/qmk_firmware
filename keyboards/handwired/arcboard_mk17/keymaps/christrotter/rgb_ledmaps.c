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
#include "arcboard_mk17.h"

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;

    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
        if (is_shifted) {
            set_rgb_range(RGB_IND_L_MIN, RGB_IND_L_MAX, INDICATOR_SHIFT);
        } else if (is_oneshot) {
            set_rgb_range(RGB_IND_L_MIN, RGB_IND_L_MAX, INDICATOR_SHIFT);
        } else if (set_scrolling) {
            set_rgb_range(RGB_IND_L_MIN, RGB_IND_L_MAX, HSV_ORANGE);
        } else {
            set_rgb_range(RGB_IND_L_MIN, RGB_IND_L_MAX, INDICATOR_BG);
        }
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L0);
                set_rgb_range(RGB_FAL2_MIN, RGB_FAL2_MAX, FAL2_L0);
                break;
            case 1:
                set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L1);
                set_rgb_range(RGB_FAL2_MIN, RGB_FAL2_MAX, FAL2_L1);
                break;
            case 2:
                set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L2);
                set_rgb_range(RGB_FAL2_MIN, RGB_FAL2_MAX, FAL2_L2);
                break;
            case 3:
                set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L3);
                set_rgb_range(RGB_FAL2_MIN, RGB_FAL2_MAX, FAL2_L3);
                break;
            default:
                break;
        }
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
        if (is_shifted) {
            set_rgb_range(RGB_IND_R_MIN, RGB_IND_R_MAX, INDICATOR_SHIFT);
        } else if (is_oneshot) {
            set_rgb_range(RGB_IND_R_MIN, RGB_IND_R_MAX, INDICATOR_SHIFT);
        } else if (set_scrolling) {
            set_rgb_range(RGB_IND_R_MIN, RGB_IND_R_MAX, HSV_ORANGE);
        } else {
            set_rgb_range(RGB_IND_R_MIN, RGB_IND_R_MAX, INDICATOR_BG);
        }
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_FAL3_MIN, RGB_FAL3_MAX, FAL3_L0);
                set_rgb_range(RGB_FAL4_MIN, RGB_FAL4_MAX, FAL4_L0);
                break;
            case 1:
                set_rgb_range(RGB_FAL3_MIN, RGB_FAL3_MAX, FAL3_L1);
                set_rgb_range(RGB_FAL4_MIN, RGB_FAL4_MAX, FAL4_L1);
                break;
            case 2:
                set_rgb_range(RGB_FAL3_MIN, RGB_FAL3_MAX, FAL3_L2);
                set_rgb_range(RGB_FAL4_MIN, RGB_FAL4_MAX, FAL4_L2);
                break;
            case 3:
                set_rgb_range(RGB_FAL3_MIN, RGB_FAL3_MAX, FAL3_L3);
                set_rgb_range(RGB_FAL4_MIN, RGB_FAL4_MAX, FAL4_L3);
                break;
            default:
                break;
        }
    }

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
