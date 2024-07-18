/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 8
#endif // VIA_ENABLE

#undef POINTING_DEVICE_TASK_THROTTLE_MS
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

// #undef  PRINTF_SUPPORT_DECIMAL_SPECIFIERS
// #define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1

#define MACCEL_TAKEOFF 2.0 // lower/higher value = curve takes off more smoothly/abrubtly
#define MACCEL_GROWTH 0.25 // lower/higher value = curve reaches its upper limit slower/faster
#define MACCEL_OFFSET 2.2  // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 0.2   // upper limit of accel curve (maximum acceleration factor)
// #define MACCEL_USE_KEYCODES

#define EECONFIG_USER_DATA_SIZE 20

#define MACCEL_DEBUG
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1

#define POINTING_DEVICE_ROTATION_90
