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
#pragma once

#include "quantum.h"

#define LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55,            RT_51, RT_52, RT_53, RT_54, RT_55, \
    F1_01, F1_02, F1_03, F1_04, F1_05, F1_06,     F3_01, F3_02, F3_03, F3_04, F3_05, F3_06, \
    F1_07, F1_08, F1_09, F1_10, F1_11, F1_12,     F3_07, F3_08, F3_09, F3_10, F3_11, F3_12, \
    F2_01, F2_02, F2_03, F2_04, F2_05, F2_06,     F4_01, F4_02, F4_03, F4_04, F4_05, F4_06, \
    F2_07, F2_08, F2_09, F2_10, F2_11, F2_12,     F4_07, F4_08, F4_09, F4_10, F4_11, F4_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06,     IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11,            IR_07, IR_08, IR_09, IR_10, IR_11 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, \
    F1_01, F1_02, F1_03, F1_04, F1_05, F1_06, \
    F1_07, F1_08, F1_09, F1_10, F1_11, F1_12, \
    F2_01, F2_02, F2_03, F2_04, F2_05, F2_06, \
    F2_07, F2_08, F2_09, F2_10, F2_11, F2_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, \
    F3_01, F3_02, F3_03, F3_04, F3_05, F3_06, \
    F3_07, F3_08, F3_09, F3_10, F3_11, F3_12, \
    F4_01, F4_02, F4_03, F4_04, F4_05, F4_06, \
    F4_07, F4_08, F4_09, F4_10, F4_11, F4_12, \
    IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IR_07, IR_08, IR_09, IR_10, IR_11 \
}
typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];
void set_rgb_range(uint8_t led_start, uint8_t led_last, int val, int layer);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

bool rgb_matrix_indicators_keymap(void);
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
