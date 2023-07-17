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
    LAYER_COLEMAK,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
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

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define ADJUST MO(LAYER_ADJUST)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

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
        KC_LCTL,         PT_Z,         KC_X,         KC_C,         KC_V,           KC_B,        KC_N,         KC_M,      KC_COMM,       KC_DOT,         PT_SLSH, KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                                  KC_BSPC,       KC_SPC, LGUI_T(KC_DEL),      KC_TAB,       KC_ENT,
                                                                   C_LT,          LOWER,       RAISE
  //                                           ╰─────────────────────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC,KC_GRAVE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS,  KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,      KC_P0, _______,
                                           CW_TOGG, _______,     ADJUST
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,      KC_F1,      KC_F2,      KC_F3,      KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PSCR,    KC_RALT,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MNXT,    XXXXXXX, KC_HOME,   KC_UP, KC_PGUP, KC_MNXT, KC_VOLU,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_PAUS,    KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT, KC_MPLY,    XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_MPLY, KC_MUTE,
  // ├──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_MPRV,    XXXXXXX,  KC_END, XXXXXXX, KC_PGDN, KC_MPRV, KC_VOLD,
  // ╰──────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                           _______,    _______, _______,    _______, _______,
                                                       CW_TOGG,  ADJUST,    _______
  //                                  ╰─────────────────────────────────╯ ╰──────────────────╯
  ),

    [LAYER_ADJUST] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
       RGB_VAI,           _______, _______, _______, EE_CLR,  QK_BOOT,               QK_BOOT, EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       RGB_VAD,           _______, _______, _______, _______, _______,               S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       _______,           _______, _______, _______, _______, _______,               XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       _______,           _______, _______, _______, _______, _______,               KC_BTN2, KC_BTN1,  SNIPING, DRGSCRL, TG(LAYER_POINTER), XXXXXXX,
  // ╰────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                            _______, _______, _______,               KC_BTN3, KC_BTN1,
                                           _______, TG(LAYER_POINTER),               KC_BTN2
  //                                           ╰─────────────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_COLEMAK] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
        KC_ESC,         KC_1,         KC_2,         KC_3,         KC_4,    KC_5,       KC_6,             KC_7,        KC_8,         KC_9,            KC_0, KC_MINS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      KC_GRAVE,         KC_Q, RALT_T(KC_W),         KC_F,         KC_P,    KC_B,       KC_J,             KC_L,        KC_U, RALT_T(KC_Y),         KC_SCLN, KC_BSLS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       KC_LSFT, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T),    KC_G,       KC_M,    RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I),    RGUI_T(KC_O), KC_QUOT,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       KC_LCTL,         PT_Z,         KC_X,         KC_C,         KC_D,    KC_V,       KC_K,            KC_H,      KC_COMM,       KC_DOT,         PT_SLSH, KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                                 KC_BSPC,       KC_SPC,  KC_DEL,      KC_TAB,          KC_ENT,
                                                                  C_LT,   LOWER,      RAISE
  //                                           ╰─────────────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_GAME] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
        KC_ESC,         KC_1,         KC_2,         KC_3,         KC_4,    KC_5,       KC_6,             KC_7,        KC_8,         KC_9,            KC_0, KC_MINS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
        KC_TAB,         KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,       KC_Y,             KC_U,        KC_I,         KC_O,            KC_P, KC_BSLS,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       KC_LSFT,         KC_A,         KC_S,         KC_D,         KC_F,    KC_G,       KC_H,             KC_J,        KC_K,         KC_L,         KC_SCLN, KC_QUOT,
  // ├────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
       KC_LCTL,         PT_Z,         KC_X,         KC_C,         KC_V,    KC_B,       KC_N,            KC_M,      KC_COMM,       KC_DOT,         PT_SLSH, KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                                  _______,     _______,  _______,    _______,         _______,
                                                                  C_LT,  _______,    _______
  //                                           ╰─────────────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case LSFT_T(KC_T):
        case RSFT_T(KC_N): // Immediately select the hold action when another key is pressed.
            return true;
        default: // Do not select the hold action when another key is pressed.
            return false;
    }
}

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
                        default_layer_set(1UL << LAYER_COLEMAK);
                        current_default_layer = LAYER_COLEMAK;
                        break;
                    default:
                    case LAYER_COLEMAK:
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
  [LAYER_LOWER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
           hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,      hTORQ,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,      hLRED,      hBLUE,      hBLUE,      hBLUE,      hLRED,      hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,       hOFF,      hLRED,      hBLUE,      hBLUE,      hBLUE,      hLRED,      hLRED,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,      hLRED,      hBLUE,      hBLUE,      hBLUE,      hLRED,      hLRED,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,      hBLUE,       hOFF,
                                                           hCYAN,      hLRED,      hLRED
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_RAISE] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
           hLRED,       hOFF,       hOFF,       hOFF,       hOFF,      hCYAN,        hOFF,      hBLUE,    hORANGE,      hBLUE,      hCYAN,      hCYAN,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hRED,       hOFF,       hOFF,       hOFF,       hOFF,      hCYAN,        hOFF,    hORANGE,    hORANGE,    hORANGE,      hCYAN,      hCYAN,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,      hPINK,      hPINK,      hPINK,      hPINK,      hCYAN,        hOFF,      hBLUE,       hOFF,      hBLUE,      hCYAN,      hCYAN,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,        hOFF,       hOFF,
                                                           hCYAN,      hLRED,       hLRED
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_ADJUST] = LAYOUT(
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
            hOFF,       hOFF,       hOFF,       hOFF,       hRED,       hRED,       hRED,       hRED,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,      hCYAN,      hCYAN,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,      hPINK,      hPINK,      hCYAN,      hCYAN,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,      hPINK,      hPINK,
                                                            hOFF,      hLRED,      hPINK
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_GAME] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,    hPURPLE,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,    hPURPLE,    hPURPLE,    hPURPLE,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
            hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                                hOFF,       hOFF,       hOFF,       hOFF,       hOFF,
                                                            hOFF,      hLRED,      hLRED
  //                                            ╰─────────────────────────────╯ ╰─────────────────────╯
  ),
  [LAYER_COLEMAK] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────────────────────────────╮
           hPINK,      hPINK,      hPINK,      hPINK,      hPINK,      hPINK,       hPINK,      hPINK,      hPINK,      hPINK,      hPINK,      hPINK,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,      hCYAN,      hCYAN,      hCYAN,      hCYAN,    hPURPLE,     hPURPLE,      hCYAN,      hCYAN,      hCYAN,      hCYAN,    hPURPLE,
  // ├────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────┤
         hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,     hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,    hPURPLE,
  // ╰────────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────────────────────────────╯
                                               hCYAN,      hCYAN,      hTORQ,      hTORQ,       hCYAN,
                                                           hCYAN,      hLRED,      hLRED
  //                                       ╰──────────────────────────────────╯ ╰─────────────────────╯
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
