// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// SPI configuration
#define SPI_MATRIX_DIVISOR 16
#define SPI_DRIVER SPID1

#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP9
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP5

// two shift registers for rows(74HC595), two for cols(74HC589)
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2

