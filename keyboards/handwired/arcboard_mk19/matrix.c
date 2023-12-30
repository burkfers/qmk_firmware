// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "spi_master.h"

// what are these used for? an array of row/col count.
// why = ROWS? COLS is a default setting for col pins
// rows was actually MATRIX_ROW_PINS, another default, in quantum/matrix.c
// static SPLIT_MUTABLE_ROW pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
// this seems to be just 'row/col count' so we can use an analogue
static const uint16_t row_values[MATRIX_ROWS] = {0};
static const uint16_t col_values[MATRIX_COLS] = {0};
static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

// the on-start block to get our SPI setup ready for matrix scanning
void matrix_init_custom(void) {
    // we use two CS pins - one for each shift register chain, rows and cols
    // setting CS to HIGH = 'not polling/selected'
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);

    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    
    spi_init();
}

// we write row data to the 595 shift register chain
// how does this work?
static inline void write_to_row(uint16_t value) {
    // message is length of 2; what is this doing exactly?
    // this is the SPI data that is being written out to the shift registers
    // KarlK90's code
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

// we need to read col data from the 589 shift register chain
static inline uint8_t read_cols(void) {
    // this should be the spi_receive block
    // why is this doing stop/start...and the other is not? cuz copypasta, sir
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, 0, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
    spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    spi_stop(); 

    uint8_t c = readPin(col_values[0]); // this is not needed

    for (uint8_t col = 1; col < MATRIX_COLS; col++) {
        c |= (readPin(col_values[col]) << col);
    }
    return c;
}

// custom_matrix=lite - our custom matrix scan over SPI/shift registers
bool matrix_scan_custom(matrix_row_t current_matrix[]) {

    // we set each row HIGH, one by one, and poll all col state each time.
    // we are looking for cols that are HIGH
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // set the row to HIGH
        set_row_high(row);

        // now read the collective col state
        uint8_t cols = read_cols();
        // loop through the received cols state data
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            current_matrix[col] |= (((cols & (1 << col)) ? 1 : 0) << row);
        }
    }

    // Check if we've changed, return the last-read data
    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;


/*
    We want to:
    - for each row
      - set row HIGH
      - get all cols HIGH/LOW
    - compare this against our existing matrix
    - return changed bool
*/

}