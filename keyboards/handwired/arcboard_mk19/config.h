// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBOUNCE 10

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
// #define ROWS (uint16_t[]){0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001}
// #define ROWS (uint16_t[]){0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001}
// Rows that should be scanned, by their bit position and thus row index.
// #define ROWS { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }
// this makes sense if they are == PCB-ROW0, like the physical pin location
#define ROWS { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }

// Split settings
#if defined(SPLIT_KEYBOARD)
    // #define EE_HANDS // replace this w. pin-handedness                           // cuz we are using hand-targeted flashing, which sets eeprom handednesss
    #define SPLIT_HAND_PIN GP2
    #define SERIAL_USART_FULL_DUPLEX
    #define SERIAL_USART_PIN_SWAP
    #define SERIAL_USART_TX_PIN GP0             // I could never get full-duplex working; this is the only config needed for half-duplex
    #define SERIAL_USART_RX_PIN GP1
    #define SERIAL_PIO_USE_PIO1                 // using PIO0 i get a lot of dropped packets; none using PIO1
    #define SERIAL_USART_SPEED 800000
    #define SPLIT_LAYER_STATE_ENABLE            // docs say use this if you are using split and rgb lighting per layer // this added 20 to scanrate???
#endif