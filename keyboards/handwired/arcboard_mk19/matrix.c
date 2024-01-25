// Copyright 2018-2022 Nick Brassel (@tzarc)
// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// Copyright 2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"
#include "wait.h"
#include "print.h"

// these are the lists of hex values
static const uint16_t row_values[MATRIX_COLS] = ROWS;

static const int msize = MATRIX_ROWS * sizeof(matrix_row_t);
static matrix_row_t prev_matrix[MATRIX_ROWS];

void matrix_init_custom(void) {
    // we use two CS pins - one for each shift register chain, rows and cols
    // setting them high turns off the shift register
    
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);

    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);

    spi_init();


    matrix_io_delay();
    
}

// we write row data to the entire 74HC595 shift register chain
static inline void write_to_rows(uint16_t value) {
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();

}

static inline void set_row_high(uint8_t row) {
    write_to_rows(row_values[row]); 
}

// we need to read col data from the 74HC589 shift register chain
static inline uint16_t read_all_cols(void) {
    uint16_t col_pin_state = 0;
    
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
    spi_receive((uint8_t*)prev_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT);
    spi_stop(); 
    
    col_pin_state = prev_matrix[0] | (prev_matrix[1] >> 8);

    return col_pin_state;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memset(current_matrix, 0, msize);
    
    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);
        uint16_t temp_col_state = read_all_cols();
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            prev_matrix[current_col] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, prev_matrix, msize) != 0;
    if (matrix_has_changed) {
        printf("Matrix has changed.");
        memcpy(prev_matrix, current_matrix, msize);
    }
    return matrix_has_changed;
}