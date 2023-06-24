// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);

enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _MOUSE,
    _SYMBOLS,
    _NAV,
};

#define _MACROS _MOUSE

// clang-format off
    /* row,col
     * .------+------+------+------+------+------.                                                       .------+------+------+------+------+------.
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                                       |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                                                       |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |                                                       |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |                                                       |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |
     * '------+------+------+------+------+------+------+------+------.             .------+------+------+------+------+------+------+------+------'
     *        |  trackball  |  5,1 |  5,2 |------|  6,1 |  6,2 |  6,3 |             |  6,1 |  6,2 |  6,3 |------|  5,1 |  5,2 |  trackball  |
     *        '-------------+------+------+------+------+------+------'             +------+------+------+------+------+------+-------------'
     *                      |  5,3 |  5,4 |  5,5 |  6,3 |  6,4 |                    |  6,3 |  6,4 |             |  5,3 |  5,4 |  5,5 |
     *                      '------+------+------+------+------' .------.  .------. '------+------'             +------+------+------'
     *                             |  5,6 |          |  6,5 |    |  6,6 |  |  6,6 |     |  6,5 |                       |  5,6 |
     *                             '------'          '------'    '------'  '------'     '------'                       '------'
     * 5,1-5,6  = thumb keys
     * 6,1-6,4  = 5-way/dpad up/down/left/right
     * 6,5      = 5-way/dpad button
     * 6,6      = falcon button
     */
// clang-format on

#define LAYOUT( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, BL_11,     RT_51, RT_52, RT_53, RT_54, RT_55, BR_11, \
    LT_61, LT_62, LT_63, LT_64, LT_65, BL_21,     RT_61, RT_62, RT_63, RT_64, RT_65, BR_21, \
    F1_01, F1_02, F1_03, F1_04, F1_05, F1_06,     F3_01, F3_02, F3_03, F3_04, F3_05, F3_06, \
    F1_07, F1_08, F1_09, F1_10, F1_11, F1_12,     F3_07, F3_08, F3_09, F3_10, F3_11, F3_12, \
    F2_01, F2_02, F2_03, F2_04, F2_05, F2_06,     F4_01, F4_02, F4_03, F4_04, F4_05, F4_06, \
    F2_07, F2_08, F2_09, F2_10, F2_11, F2_12,     F4_07, F4_08, F4_09, F4_10, F4_11, F4_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06,     IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11,            IR_07, IR_08, IR_09, IR_10, IR_11 \
) \
{ \
    { LM_11, LM_12, LM_13, LM_14, LM_15, LM_16 }, \
    { LM_21, LM_22, LM_23, LM_24, LM_25, LM_26 }, \
    { LM_31, LM_32, LM_33, LM_34, LM_35, LM_36 }, \
    { LM_41, LM_42, LM_43, LM_44, LM_45, LM_46 }, \
    { LT_51, LT_52, LT_53, LT_54, LT_55, BL_11 }, \
    { LT_61, LT_62, LT_63, LT_64, LT_65, BL_21 }, \
    { F1_01, F1_02, F1_03, F1_04, F1_05, F1_06 }, \
    { F1_07, F1_08, F1_09, F1_10, F1_11, F1_12 }, \
    { F2_01, F2_02, F2_03, F2_04, F2_05, F2_06 }, \
    { F2_07, F2_08, F2_09, F2_10, F2_11, F2_12 }, \
    { IL_01, IL_02, IL_03, IL_04, IL_05, IL_06 }, \
    { IL_07, IL_08, IL_09, IL_10, IL_11 }, \
    { RM_11, RM_12, RM_13, RM_14, RM_15, RM_16 }, \
    { RM_21, RM_22, RM_23, RM_24, RM_25, RM_26 }, \
    { RM_31, RM_32, RM_33, RM_34, RM_35, RM_36 }, \
    { RM_41, RM_42, RM_43, RM_44, RM_45, RM_46 }, \
    { RT_51, RT_52, RT_53, RT_54, RT_55, BR_11 }, \
    { RT_61, RT_62, RT_63, RT_64, RT_65, BR_21 }, \
    { F3_01, F3_02, F3_03, F3_04, F3_05, F3_06 }, \
    { F3_07, F3_08, F3_09, F3_10, F3_11, F3_12 }, \
    { F4_01, F4_02, F4_03, F4_04, F4_05, F4_06 }, \
    { F4_07, F4_08, F4_09, F4_10, F4_11, F4_12 }, \
    { IR_01, IR_02, IR_03, IR_04, IR_05, IR_06 }, \
    { IR_07, IR_08, IR_09, IR_10, IR_11 }, \
}

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
    enum board_keycodes {
        DRAG_SCROLL,
        BOARD_SAFE_RANGE,
    };
    #define DRGSCRL DRAG_SCROLL

    bool board_get_pointer_dragscroll_enabled(void);
#endif // POINTING_DEVICE_ENABLE

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

void matrix_init_sub_kb(void);
void matrix_scan_sub_kb(void);
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record); //_user should not be in the keyboard.c
