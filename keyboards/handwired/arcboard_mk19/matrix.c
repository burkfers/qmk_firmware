// Copyright 2018-2022 Nick Brassel (@tzarc)
// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// Copyright 2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"

static const uint16_t row_values[MATRIX_ROWS] = {0};
static const uint16_t col_values[MATRIX_COLS] = {0};
static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

void matrix_init_custom(void) {
    // we use two CS pins - one for each shift register chain, rows and cols
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);

    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    
    spi_init();
}

// we write row data to the 74HC595 shift register chain
static inline void write_to_row(uint16_t value) {
    // message is length of 2; what is this doing exactly? KarlK90's code
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, 0, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2); // send data, length of 2 cuz 0xFF kind of format?
    spi_stop();
    // row should now be set HIGH
}
// um why have both of these functions, why not just one? type issue due to MATRIX_ROWS?
static inline void set_row_high(uint8_t row) {
    write_to_row(row_values[row]); 
}

// we need to read col data from the 74HC589 shift register chain
static inline uint8_t read_all_cols(void) {
    // pretty sure we need to revisit this...needs a temp_cols_matrix or something?
    uint8_t c = readPin(col_values[0]);

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, 0, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
    spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    spi_stop(); 

    for (uint8_t col = 1; col < MATRIX_COLS; col++) {
        c |= (readPin(col_values[col]) << col);
    }
    return c;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    // we set each row HIGH, one by one, and poll all col state each time.
    // we need to build a fresh matrix scan so we can compare
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row); // set this iteration's row shift register data output pin to HIGH

        // now read the collective col state - this happens for each row
        uint8_t temp_col_state = read_all_cols();
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            // why is this current_matrix (mlego code)
            // oh, they use prev/current(mlego) vs. current/temp(tzarc) vs. current/input(karl)
            // qmk uses raw_matrix/curr_matrix
            temp_matrix[current_col] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    // Check if we've changed, return the last-read data
    matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;

}