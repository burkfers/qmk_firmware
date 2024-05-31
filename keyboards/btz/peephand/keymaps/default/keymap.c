// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,   KC_1,    KC_2,    KC_3,   KC_4,
        KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,
        KC_LSFT,  KC_A,    KC_S,    KC_D,   KC_F,
        MO(1),    KC_Z,    KC_X,    KC_C
    ),
    [1] = LAYOUT(
        PH_SMOD, PH_IDZ,  PH_ODZ,  PH_ANGL, PH_SMOD,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
