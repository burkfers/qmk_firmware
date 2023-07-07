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

void set_rgb_range(uint8_t first_led, uint8_t last_led, int val, int layer) {
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
void set_rgb_led(int index, int hue, int sat, int val) {
    HSV hsv = {
        .h = hue,
        .s = sat,
        .v = 150,
    };
    if (hsv.h || hsv.s) {
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
    }
}

// todo; needs a lot of work to map to falcon layers
/*
    Flag usage:
    0x04 = per-key leds
    0x01 = Falcon-angled, FAL1, FAL3
    0x02 = Falcon-flat, FAL2, FAL4
    0x08 = indicator panel
*/

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (is_keyboard_left()) {
            // set LEFT per-key leds by ledmap
            if (HAS_FLAGS(g_led_config.flags[i], 0x04)) {
                set_rgb_range(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
            }
            // set LEFT falcon colour by layer
            switch(get_highest_layer(layer_state|default_layer_state)) {
                case 0:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL1_L0);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL2_L0);
                    }
                    break;
                case 1:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL1_L1);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL2_L1);
                    }
                    break;
                case 2:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL1_L2);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL2_L2);
                    }
                    break;
                case 3:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL1_L3);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL2_L3);
                    }
                    break;
                default:
                    break;
            }
        } else {
            // set RIGHT per-key leds by ledmap
            if (HAS_FLAGS(g_led_config.flags[i], 0x04)) {
                set_rgb_range(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
            }
            // set RIGHT falcon colour by layer
            switch(get_highest_layer(layer_state|default_layer_state)) {
                case 0:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL3_L0);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL4_L0);
                    }
                    break;
                case 1:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL3_L1);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL4_L1);
                    }
                    break;
                case 2:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL3_L2);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL4_L2);
                    }
                    break;
                case 3:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, FAL3_L3);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, FAL4_L3);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    if (is_shifted) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_SHIFT);
            }
        }
    } else {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_BG);
            }
        }
    }
    bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;
    if (is_oneshot) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_SHIFT);
            }
        }
    } else {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_BG);
            }
        }
    }
    if (set_scrolling) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, HSV_ORANGE);
            }
        }
    }

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
