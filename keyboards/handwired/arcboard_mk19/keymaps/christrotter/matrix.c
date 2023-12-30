// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "spi_master.h"

/*
// for the config.h
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2
*/
// what are these used for?
static const uint16_t row_values[MATRIX_ROWS] = ROWS;
static const uint16_t col_values[MATRIX_COLS] = COLS;

// the on-start block to get our SPI setup ready for matrix scanning
void matrix_init_custom(void) {
    // we use two CS pins - one for each shift register chain, rows and cols
    // setting CS to HIGH = 'not polling/selected'
    setPinOutput(SPI_COL_CS_PIN);
    writePinHigh(SPI_COL_CS_PIN);

    setPinOutput(SPI_ROW_CS_PIN);
    writePinHigh(SPI_ROW_CS_PIN);
    
    spi_init();
}

// we write row data to the 595 shift register chain
// how does this work?
static inline void write_rows(uint16_t value) {
    // message is two parts? what is this doing exactly?
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    writePinLow(SPI_ROW_CS_PIN); // enable pin
    spi_transmit(message, 2); // send data
    writePinHigh(SPI_ROW_CS_PIN); // disable pin
    matrix_output_select_delay(); // not sure why this is here...
}
static inline void set_row_high(uint8_t row) {
    write_rows(row_values[row]);
}

// we need to read col data from the 589 shift register chain
static inline uint8_t read_cols(void) {
    // this should be the spi_receive block
    spi_start(SPI_COL_CS_PIN, false, 0, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
    spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_col_t));
    spi_stop();

    uint8_t r = readPin(col_pins[0]); // this is not needed

    for (uint8_t col = 1; col < MATRIX_colS; col++) {
        c |= (readPin(col_pins[col]) << col);
    }
    return c;
}

// custom_matrix=lite - our custom matrix scan over SPI/shift registers
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memset(current_matrix, 0, msize);

    // we set each row HIGH, one by one, and poll all col state each time.
    // we are looking for cols that are HIGH
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // set the row to HIGH
        set_row_high(row);

        // now read the collective col state
        uint8_t cols = read_cols();
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            current_matrix[col] |= (((cols & (1 << col)) ? 1 : 0) << row);
        }
    }
    bool changed = (memcmp(current_matrix, prev_matrix, msize) != 0);
    memcpy(prev_matrix, current_matrix, msize);
    return changed;



    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);

        uint8_t cols = read_cols();
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            current_matrix[col] |= (((cols & (1 << col)) ? 1 : 0) << col);
        }
    }

/*
    We want to:
    - for each row
      - set row HIGH
      - get all cols HIGH/LOW
    - compare this against our existing matrix
    - return changed bool
*/




    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;
}