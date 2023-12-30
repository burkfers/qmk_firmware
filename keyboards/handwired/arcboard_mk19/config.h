// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// SPI configuration
#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP1
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP2
#define SPI_MATRIX_DIVISOR 16
#define SPI_DRIVER SPID1

#define SPI_MISO_PIN GP3
#define SPI_MOSI_PIN GP4
#define SPI_SCK_PIN GP5

// two shift registers for rows(74HC595), two for cols(74HC589)
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
