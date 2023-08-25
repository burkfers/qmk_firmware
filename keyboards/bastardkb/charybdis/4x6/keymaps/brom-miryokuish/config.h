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
#pragma once

/* Charybdis-specific features. */
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 500
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
#define CHARYBDIS_MINIMUM_SNIPING_DPI 100
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100

#define CHARYBDIS_CONFIG_SYNC

//#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#define EE_HANDS

#define TAPPING_TERM 200
#define BILATERAL_COMBINATIONS 500
#define PERMISSIVE_HOLD

#define RGB_MATRIX_TIMEOUT 1200000
#define ENABLE_COMPILE_KEYCODE

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 800
#define AUTO_MOUSE_DEBOUNCE 50

#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
