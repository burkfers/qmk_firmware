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

    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        uint16_t col_pin_state;
        uint8_t temp_receive[MATRIX_COLS_SHIFT_REGISTER_COUNT] = {0};

        set_row_high(row); // write row high via 595 shift registers

        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
        spi_receive((uint8_t*)temp_receive, MATRIX_COLS_SHIFT_REGISTER_COUNT); // receive col data via 589 shift registers
        spi_stop(); 

        col_pin_state = temp_receive[0] | (temp_receive[1] << 8);
        if (col_pin_state != 0) {
            printf("row %u: col received: %u \n", row, col_pin_state);
        }

        temp_matrix[row] = col_pin_state;
    }

    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;
}