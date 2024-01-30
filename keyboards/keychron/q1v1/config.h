<<<<<<< HEAD
<<<<<<<< HEAD:keyboards/keychron/q1v1/config.h
/* Copyright 2021 @ Keychron(https://www.keychron.com)
========
/* Copyright 2022 DZTECH <moyi4681@live.cn>
>>>>>>>> develop:keyboards/kbdfans/odin75/config.h
=======
/* Copyright 2021 @ Keychron(https://www.keychron.com)
>>>>>>> develop
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

<<<<<<< HEAD
<<<<<<<< HEAD:keyboards/keychron/q1v1/config.h
/* RGB Matrix Driver Configuration */
#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC
=======
/* RGB Matrix Driver Configuration */
#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_VCC_VCC
>>>>>>> develop

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {0,1} }

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* Encoder Configuration*/
#define ENCODER_DEFAULT_POS 0x3

/* Disable RGB lighting when PC is in suspend */
<<<<<<< HEAD
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
========
/* OLED SPI Defines */
#define OLED_DISPLAY_128X64
#define OLED_IC OLED_IC_SH1106

/* OLED SPI Pins */
#define OLED_DC_PIN GP24
#define OLED_CS_PIN GP22
#define OLED_RST_PIN GP23

/* Shift OLED columns by 2 pixels */
#define OLED_COLUMN_OFFSET 2

/* Divisor for OLED */
#define OLED_SPI_DIVISOR 4

/* ChibiOS SPI definitions */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP26
#define SPI_MOSI_PIN GP27
#define SPI_MISO_PIN GP28
>>>>>>>> develop:keyboards/kbdfans/odin75/config.h
=======
#define RGB_MATRIX_SLEEP

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
>>>>>>> develop
