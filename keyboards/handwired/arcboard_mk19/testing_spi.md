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


# More digging
- row pin connected to each col pin outputs 1,2,4,8,etc,32768

```c
spi_status_t spi_transmit(const uint8_t *data, uint16_t length);
spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}
```

```c
spi_status_t spi_receive(uint8_t *data, uint16_t length);
spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}
```

# trying to understand what's in the matrix
```c
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memset(current_matrix, 0, msize);
    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);
        uint16_t temp_col_state = read_all_cols();
        if (temp_col_state != 0) {
            // printf("col register data: %u \n", temp_col_state);
        }
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            prev_matrix[current_col] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, prev_matrix, msize) != 0;
    if (matrix_has_changed) {
        for(int i = 0; i < MATRIX_ROWS; i++) {
            printf(" %d ", current_matrix[i]); // this outputs zeros
        }
        memcpy(prev_matrix, current_matrix, msize);
        printf("Matrix has changed. \n");
    }
    return matrix_has_changed;
}
```

```
christrotter:handwired/arcpedals_mk2:2: matrix scan frequency: 3123
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
```

So the col register data has values...but the matrix is not changing...

Output of msize is 32.

```c
printf("row (%d), col register data: %u \n", row, temp_col_state);
```
This correctly changes as i move through rows.
```
christrotter:handwired/arcboard_mk19:2: row (3), col register data: 2
christrotter:handwired/arcboard_mk19:2: row (2), col register data: 2
```

I found current/prev was being mixed up.  Removed 'prev' and replaced w. 'temp', cuz i get that naming logic now.
Current = what is in memory
Temp = the fresh reading of pins that we may or may not write to memory

```
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  10239  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65534  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  8445  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  8256  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
```

Some of these values are wack tho.

Apparently: `sizeof(matrix_row_t) = 2`

I re-looked at tzarc's implementation and fixed some stuff.
Now i get...
```
➜  arcboard_mk19 git:(arcboard-series) ✗ vbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
vvvvvvvvZXCVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
```

The key-up is not working or something.
Verified this with the qmk tester.

debounce: true does not help
