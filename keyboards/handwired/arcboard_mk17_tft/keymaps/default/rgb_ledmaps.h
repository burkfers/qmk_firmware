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

#define LEDMAP( LM_11 ) { LM_11 }
typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];
void set_rgb_range(uint8_t led_start, uint8_t led_last, int val, int layer);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

bool rgb_matrix_indicators_keymap(void);
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
