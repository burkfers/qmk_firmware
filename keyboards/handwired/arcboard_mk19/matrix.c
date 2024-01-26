// Copyright 2018-2022 Nick Brassel (@tzarc)
// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// Copyright 2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"
#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif

static const uint16_t row_values[MATRIX_COLS] = ROWS;

void matrix_init_custom(void) {
    // set both CS pins HIGH -> shift register reading/writing = off
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    spi_init();
}

static inline void write_to_rows(uint16_t value) {
    // Burkfers: Message is 2 8 bit integers. Expression chops up value, a 16 bit integer, into two halves - necessary because spi_transmit below expects an array of bytes.
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();
}

static inline void set_row_high(uint8_t row) {
    write_to_rows(row_values[row]); 
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};
    matrix_io_delay();

    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        uint16_t col_pin_state;

        set_row_high(row); // write row high via 595 shift registers

        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
        spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t)); // receive col data via 589 shift registers
        spi_stop(); 

        // feel like i don't know what is going on here...some bitshifting
        // presumes that the array temp_matrix[] is only 2 items; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
        col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);
        
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            temp_matrix[current_col] |= (((col_pin_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;
}