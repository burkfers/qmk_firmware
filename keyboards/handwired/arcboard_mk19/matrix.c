// Copyright 2018-2022 Nick Brassel (@tzarc)
// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// Copyright 2023 Stefan Kerkmann (@karlk90)
// Copyright 2023 (@burkfers)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"
#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif

// static const uint16_t row_values[MATRIX_COLS] = ROWS;
// static const uint16_t col_values[MATRIX_COLS] = COLS;
// static const uint16_t rows[] = ROWS;
static const uint16_t row_values[16] = ROWS; // divided by 2 cuz split

void matrix_init_custom(void) {
    // set both CS pins HIGH -> shift register reading/writing = off
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    spi_init();
}



static inline void write_to_rows(uint16_t value) {
    // this sends 2 bytes of data to the 595s
    // e.g. 00000000 00000001 = row0

    // uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)}; // old
    // the batching (0-7 and 8-15 at the correct shift register) of these is correct
    // but they are mapped in reverse
    printf("value: %u \n", value);
    printf("value >> 8: %u \n",(value >> 8));
    printf("(value >> 8) & 0xFF: %u \n",(value >> 8) & 0xFF);
    printf("(value & 0xFF): %u \n",(value & 0xFF));
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();
}

static inline void set_row_high(uint16_t row) {
    write_to_rows(row_values[row]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // set up an empty temp_matrix
    // loop over rows
    // loop sets row high, then polls all cols
    // cols function returns 2 bytes
    // take the col results and build row X of our temp_matrix
    // if changes, memcpy updates the matrix object that does keystrokes
    static matrix_row_t temp_matrix[16] = {0}; // split makes this blow up
    // printf("BEGIN SETTING ROWS HIGH \n");
    for (uint8_t row = 0; row < (16); row++) {
        uint8_t temp_col_receive[MATRIX_COLS_SHIFT_REGISTER_COUNT] = {0};
        uint16_t temp_col_state;

        // printf("Starting row scan at: %d \n", row);
        set_row_high(row); // write row high via 595 shift registers

        // this calls the 589s and pulls 2 bytes of data, returns a uint16
        // e.g. 00000010 00000001 = col10 & col0
        // mash those two bytes together and return uint16 'col_pin_state'

        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
        spi_stop();
        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
        spi_receive((uint8_t*)temp_col_receive, MATRIX_COLS_SHIFT_REGISTER_COUNT); // receive col data via 589 shift registers
        spi_stop();

        temp_col_state = temp_col_receive[0] | (temp_col_receive[1] << 8);
        if (temp_col_state != 0) {
            printf("row/row_val/col: [ %u / %u / %u ] \n", row, row_values[row], temp_col_state);
            // printf("row_t size: %u \n", sizeof(matrix_row_t)); // this is 1, btw
        }
        // for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        //     temp_matrix[row] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        // }
        temp_matrix[row] = temp_col_state;
    }
    // printf("END SETTING ROWS HIGH \n");
    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
        // printf("MATRIX HAS CHANGED MEMCPY \n");
    }
    return matrix_has_changed;
}