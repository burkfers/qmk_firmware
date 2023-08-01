/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_GAME,
    LAYER_NUM,
    LAYER_NAV,
    LAYER_FUN,
    LAYER_MEDIA,
    LAYER_SYM,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
//#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1500
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 3
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

enum my_keycodes {
    C_LT = SAFE_RANGE // CUSTOM_LAYERTOGGLE
};

tap_dance_action_t tap_dance_actions[] = {
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
         KC_ESC,         KC_1,         KC_2,         KC_3,         KC_4,           KC_5,        KC_6,         KC_7,         KC_8,         KC_9,            KC_0, KC_MINS,
  // ├────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       KC_GRAVE,         KC_Q, RALT_T(KC_W),         KC_E,         KC_R,           KC_T,        KC_Y,         KC_U,         KC_I, RALT_T(KC_O),            KC_P, KC_BSLS,
  // ├────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
        KC_LSFT, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F),           KC_G,        KC_H, RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
  // ├────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
        KC_LCTL,         KC_Z,         KC_X,         KC_C,         KC_V,           KC_B,        KC_N,         KC_M,      KC_COMM,       KC_DOT,         KC_SLSH, KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                                  LT(LAYER_MEDIA, KC_ESC),       LT(LAYER_NAV, KC_SPC), LT(LAYER_POINTER, KC_TAB),      LT(LAYER_SYM, KC_ENT), LT(LAYER_NUM,KC_BSPC),
                                                                   C_LT,          CW_TOGG,       LT(LAYER_FUN,KC_DEL)
  //                                           ╰─────────────────────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NUM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6, KC_F7,   KC_F8,     KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,    XXXXXXX, XXXXXXX, XXXXXXX, KC_ALGR, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_DOT,    KC_0, KC_MINS,    XXXXXXX, XXXXXXX,
                                           CW_TOGG, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,      KC_F1,      KC_F2,      KC_F3,      KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PSCR,    KC_ALGR,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MNXT,    XXXXXXX, C(KC_Y), C(KC_V), C(KC_X), C(KC_Z), XXXXXXX,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PAUS,    KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT, KC_MPLY,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, CW_TOGG, XXXXXXX,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MPRV,    KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                           XXXXXXX,    XXXXXXX, XXXXXXX,     KC_ENT, KC_BSPC,
                                                       CW_TOGG, XXXXXXX,     KC_DEL
  //                                  ╰─────────────────────────────────╯ ╰──────────────────╯
  ),

    [LAYER_FUN] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,    XXXXXXX, XXXXXXX, XXXXXXX, KC_ALGR, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_APP,  KC_SPC,  KC_TAB,    XXXXXXX, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_MEDIA] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,      KC_F1,      KC_F2,      KC_F3,      KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PSCR,    KC_ALGR,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MNXT,    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, XXXXXXX,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PAUS,    KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT, KC_MPLY,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, XXXXXXX,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MPRV,    KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                           XXXXXXX,    XXXXXXX, XXXXXXX,     KC_ENT, KC_BSPC,
                                                       CW_TOGG, XXXXXXX,     KC_DEL
  //                                  ╰─────────────────────────────────╯ ╰──────────────────╯
  ),
     [LAYER_SYM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,    XXXXXXX, XXXXXXX, XXXXXXX, KC_ALGR, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_LPRN, KC_RPRN, KC_UNDS,    XXXXXXX, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_POINTER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
       RGB_VAI,           _______, _______, QK_MAKE, EE_CLR,  QK_BOOT,               QK_BOOT, EE_CLR, QK_MAKE, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       RGB_VAD,           _______, _______, _______, _______, _______,               S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       _______,           _______, _______, _______, _______, _______,               XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       _______,           _______, _______, _______, _______, _______,               KC_BTN2, KC_BTN1,  SNIPING, DRGSCRL, TG(LAYER_POINTER), XXXXXXX,
  // ╰────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                            _______, _______, _______,               KC_BTN3, KC_BTN1,
                                           _______, TG(LAYER_POINTER),                 KC_BTN2
  //                                           ╰─────────────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_GAME] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
        KC_ESC,         KC_1,         KC_2,         KC_3,         KC_4,    KC_5,       KC_6,             KC_7,        KC_8,         KC_9,            KC_0, KC_MINS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
          KC_T,       KC_TAB,         KC_Q,         KC_W,         KC_E,    KC_R,       KC_Y,             KC_U,        KC_I,         KC_O,            KC_P, KC_BSLS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
          KC_G,      KC_LSFT,         KC_A,         KC_S,         KC_D,    KC_F,       KC_H,             KC_J,        KC_K,         KC_L,         KC_SCLN, KC_QUOT,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
          KC_B,      KC_LCTL,         KC_Z,         KC_X,         KC_C,    KC_V,       KC_N,            KC_M,      KC_COMM,       KC_DOT,         KC_SLSH, KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                                  _______,     _______,  _______,    _______,         _______,
                                                                  C_LT,  _______,    _______
  //                                           ╰─────────────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case C_LT:
            if(record->event.pressed) {
                static uint8_t current_default_layer = LAYER_BASE;
                switch(current_default_layer) {
                    case LAYER_BASE:
                        default_layer_set(1UL << LAYER_GAME);
                        current_default_layer = LAYER_GAME;
                        break;
                    case LAYER_GAME:
                    default:
                        default_layer_set(1UL << LAYER_BASE);
                        current_default_layer = LAYER_BASE;
                        break;
                };
            } else {

            }
            return false; // no further processing
        default:
            return true; // process elsewhere
    }
}

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            // rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            // rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        //layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        // rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

#ifdef RGB_MATRIX_ENABLE
enum colors {
    hOFF = 0,
    hPURPLE,
    hPINK,
    hCYAN,
    hTORQ,
    hLRED,
    hBLUE,
    hORANGE,
    hRED
};

// clang-format off
const uint8_t PROGMEM ledmaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
           hPINK,      hPINK,      hPINK,      hPINK,      hPINK,      hPINK,       hPINK,      hPINK,      hPINK,      hPINK,      hPINK,      hPINK,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                               hCYAN,      hCYAN,      hTORQ,      hTORQ,       hCYAN,
                                                           hCYAN,      hLRED,      hLRED
  //                                       ╰──────────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_NUM] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_NAV] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_FUN] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_MEDIA] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_SYM] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_POINTER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_GAME] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,       hOFF,       hOFF
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
};
// clang-format on

const HSV hsv_colors[] = {
    [hOFF]      = {  0,   0,   0},
    [hPURPLE]   = {205, 255, 255},
    [hPINK]     = {251, 223, 255},
    [hCYAN]     = {128, 255, 255},
    [hTORQ]     = {120, 255, 204},
    [hLRED]     = {255, 239, 255},
    [hBLUE]     = {170, 215, 221},
    [hORANGE]   = { 20, 208, 255},
    [hRED]      = {  0, 255, 255}
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        int layer = get_highest_layer(layer_state|default_layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for(uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if(led_min <= index && index <= led_max) {
                    uint8_t color = pgm_read_byte(&ledmaps[layer][row][col]);
                    HSV hsv = hsv_colors[color];
                    if(hsv.s > 0)
                        hsv.v = rgb_matrix_config.hsv.v;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color( index, rgb.r, rgb.g, rgb.b );
                };
            };
        };
    return false;
}
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(200, 10, 10);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}
