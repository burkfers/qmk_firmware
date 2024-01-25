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

static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

void matrix_init_custom(void) {
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    spi_init();
    matrix_io_delay(); 
}

static inline void write_to_rows(uint16_t value) {
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();

}

static inline void set_row_high(uint8_t row) {
    write_to_rows(row_values[row]); 
}

static inline uint16_t read_all_cols(void) {
    uint16_t col_pin_state = 0;

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
    spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    spi_stop(); 
    
    // feel like i don't know what is going on here...some bitshifting
    // presumes that temp_matrix[] is only 0 or 1; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
    col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);

    return col_pin_state;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);

        uint16_t temp_col_state = read_all_cols();
        // if (temp_col_state != 0) {
            printf("row (%d), col register data: %u \n", row, temp_col_state);
        // }
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            // printf("row: %d \n", row);

            temp_matrix[current_col] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        for(int i = 0; i < MATRIX_COLS; i++) {
            printf(" %d ", temp_matrix[i]); // this outputs zeros
        }
        printf("sizeof matrix_row_t: %d \n", sizeof(matrix_row_t));
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
        // printf("Matrix of size %d has changed. \n", msize);
    }
    return matrix_has_changed;
}