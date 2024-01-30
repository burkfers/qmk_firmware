/*
<<<<<<<< HEAD:keyboards/handwired/arcboard_mk9/config.h
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
========
Copyright 2022 ojthetiny

>>>>>>>> develop:keyboards/fruitykeeb/fruitbar/r2/config.h
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

<<<<<<<< HEAD:keyboards/handwired/arcboard_mk9/config.h
#include "config_common.h"

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
========
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP27
#define I2C1_SDA_PIN GP26

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
>>>>>>>> develop:keyboards/fruitykeeb/fruitbar/r2/config.h
