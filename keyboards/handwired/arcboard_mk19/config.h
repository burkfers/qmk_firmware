// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// SPI configuration
#define SPI_MATRIX_DIVISOR 16
#define SPI_MODE 0
#define SPI_DRIVER SPID1

#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP9
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP5

// two shift registers for rows(74HC595 write pin high), two for cols(74HC589 receive pin state)
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2

// 16 bits 8 per register // i think at some point we'd want COLS in case you were wanting to customize your matrix size?
// Burkfers: this is binary bit masks: 0b1000000000000000, 0b0100000000000000, 0b0010000000000000, etc. For setting exactly one bit high.
#define ROWS {0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001}