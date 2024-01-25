# testing shift registers notes


# testing the 595s
This code was sufficient for me to see 3.3v on row pins 0-7 and 0v on row pins 8-15.
Flipping the ff and 00 in message reversed the voltage readings, as expected.
```c
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    uint8_t message[2] = {0xff, 0x00};
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();
    return matrix_has_changed;
}
```

# testing the 589s


    // bool matrix_has_changed = false;
    // uint8_t message[2] = {0xff, 0x00};
    // spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    // spi_transmit(message, 2);
    // spi_stop();
// 
    // static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};
    // spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    // spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    // spi_stop();
// 
    // bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    // if (matrix_has_changed) {
    //     memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    //     printf("Matrix has changed");
    // }