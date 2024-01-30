<<<<<<<< HEAD:keyboards/enviousdesign/delirium/rgb/rgb.c
/* Copyright 2022 Adam K (@Envious-Data)
========
/* Copyright 2022 LXF-YZP(yuezp)
>>>>>>>> develop:keyboards/bestway/bestway.c
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

#include "quantum.h"

<<<<<<<< HEAD:keyboards/enviousdesign/delirium/rgb/rgb.c
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(50, 16, 16, 16); // assuming caps lock is at led #50
    } 
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 16, 16, 16); // assuming scroll lock is at led #14
    }
    if (get_highest_layer(layer_state) == 1) {
        RGB_MATRIX_INDICATOR_SET_COLOR(83, 16, 16 ,16);
    }
    return true;
}
#endif
========
#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer
);

bool led_update_kb(led_t led_state) {
    if (!led_update_user(led_state)) { return false; }
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;
    keyboard_post_init_user();
}

#endif
void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP2;
}
>>>>>>>> develop:keyboards/bestway/bestway.c
