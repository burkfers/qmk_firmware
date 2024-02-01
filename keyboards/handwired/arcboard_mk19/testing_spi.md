# testing shift registers notes

# trying to revert to full bitmasks
christrotter:handwired/arcboard_mk19:3: Receive all cols: 8 [8 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 9 [row index: 4]; col bit received: 8

christrotter:handwired/arcboard_mk19:1: Receive all cols: 1 [1 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 7 [row index: 16]; col bit received: 1
christrotter:handwired/arcboard_mk19:1: Receive all cols: 32 [32 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 7 [row index: 16]; col bit received: 32

christrotter:handwired/arcboard_mk19:3: Receive all cols: 1 [1 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 11 [row index: 1]; col bit received: 1
christrotter:handwired/arcboard_mk19:3: Receive all cols: 33 [33 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 11 [row index: 1]; col bit received: 33
christrotter:handwired/arcboard_mk19:2: Receive all cols: 32 [32 / 0]
christrotter:handwired/arcboard_mk19:2: row iteration: 11 [row index: 1]; col bit received: 32



christrotter:handwired/arcboard_mk19:1: col_pin_state: 8 [8 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 1 [row index: 1024]; col bit received: 8
christrotter:handwired/arcboard_mk19:1:
christrotter:handwired/arcboard_mk19:1: r/c 01234567
christrotter:handwired/arcboard_mk19:1: 00: 00000000
christrotter:handwired/arcboard_mk19:1: keyboard_report: 00 | 10 00 00 00 00 00




# whyfore is the iteration bumped by one
christrotter:handwired/arcboard_mk19:1: Starting row: 0
christrotter:handwired/arcboard_mk19:1: bitshifted row: 1 message:  1 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 1
christrotter:handwired/arcboard_mk19:1: bitshifted row: 2 message:  2 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 2
christrotter:handwired/arcboard_mk19:1: bitshifted row: 4 message:  4 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 3
christrotter:handwired/arcboard_mk19:1: bitshifted row: 8 message:  8 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 4
christrotter:handwired/arcboard_mk19:1: bitshifted row: 16 message:  16 / 0

printf("iteration: %u [index: %u]; col received: %u [%u / %u] \n", row, rows[row], col_pin_state, temp_receive[0],(temp_receive[1] << 8));
Trigger col1 to row15:
`iteration: 0 [index: 0]; col received: 1 [1 / 0]`



# add the extra cols/rows to the layout


# split usb-c power
Uhm need to solder the bypass... :D



# split
adding split config starts throwing this:
```c
Compiling: keyboards/handwired/arcboard_mk19/matrix.c                                              keyboards/handwired/arcboard_mk19/matrix.c: In function 'matrix_scan_custom':
keyboards/handwired/arcboard_mk19/matrix.c:32:5: error: iteration 16 invokes undefined behavior [-Werror=aggressive-loop-optimizations]
     write_to_rows(row_values[row]);
     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
keyboards/handwired/arcboard_mk19/matrix.c:38:5: note: within this loop
     for (uint16_t row = 0; row < (MATRIX_ROWS * 2); row++) {
     ^~~
cc1: all warnings being treated as errors
 [ERRORS]
 |
 |
 |
gmake: *** [builddefs/common_rules.mk:369: .build/obj_handwired_arcboard_mk19_christrotter/matrix.o] Error 1
```

We changed MATRIX_ROWS calls to be just '16', and it got farther...

## soft-serial missing
Also forgot this... `SERIAL_DRIVER = vendor` ... in rules.mk.

# no key-up
## day1
Ok, so what is the logic here...
- foreach row
  - set row pin high
  - scan all cols for matching high
  - build row in temp_matrix
- now we have a rows/cols temp_matrix
- compare temp_matrix against current_matrix
  - if no changes, done;
  - if changes, overwrite current_matrix with temp_matrix
HERE.  now what?

If I connect (row pin, count3 from left) and (col pin, count3 from left) together...
```
christrotter:handwired/arcboard_mk19:2:
christrotter:handwired/arcboard_mk19:2: r/c 0123456789ABCDEF
christrotter:handwired/arcboard_mk19:2: 00: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 01: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 02: 0001000000000000
christrotter:handwired/arcboard_mk19:2: 03: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 04: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 05: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 06: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 07: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 08: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 09: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0A: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0B: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0C: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0D: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0E: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0F: 0000000000000000
christrotter:handwired/arcboard_mk19:2: keyboard_report: 00 | 06 00 00 00 00 00
```
And then:
`➜  arcboard_mk19 git:(arcboard-series) ✗ cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc`

So it's outputting a keystroke...just not recognizing that it's been released...

If i had to guess, one set of registers is not being cleared...?

Tried another board, same result.  So either there is something dramatically wrong with the hardware, or something being missed in firmware.

## day2
is it possible the rows aren't being un-set from 'high'?

Outputting our 'message'...
```
christrotter:handwired/arcboard_mk19:1: our spi message: 128 0
christrotter:handwired/arcboard_mk19:1: our spi message: 64 0
christrotter:handwired/arcboard_mk19:1: our spi message: 32 0
christrotter:handwired/arcboard_mk19:1: our spi message: 16 0
christrotter:handwired/arcboard_mk19:1: our spi message: 8 0
christrotter:handwired/arcboard_mk19:1: our spi message: 4 0
christrotter:handwired/arcboard_mk19:1: our spi message: 2 0
christrotter:handwired/arcboard_mk19:1: our spi message: 1 0
christrotter:handwired/arcboard_mk19:1: our spi message: 0 128
christrotter:handwired/arcboard_mk19:1: our spi message: 0 64
christrotter:handwired/arcboard_mk19:1: our spi message: 0 32
christrotter:handwired/arcboard_mk19:1: our spi message: 0 16
christrotter:handwired/arcboard_mk19:1: our spi message: 0 8
christrotter:handwired/arcboard_mk19:1: our spi message: 0 4
christrotter:handwired/arcboard_mk19:1: our spi message: 0 2
christrotter:handwired/arcboard_mk19:1: our spi message: 0 1
```
So the row is just constantly cycling, good.

        for(int i = 0; i < MATRIX_ROWS; i++) {
            printf("temp_matrix: %d : %d \n", i, temp_matrix[i]); // this outputs zeros
        }
        if (col_pin_state != 0) {
            printf("col_pin_state: %u \n", col_pin_state);
        }

conclusion: Yes, they were not being 'un-set from high' cuz we were missing pull-down resistors on the col pins.  Adding those cleared up all weirdness. 

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





// static inline uint16_t read_all_cols(void) {
//     uint16_t col_pin_state = 0;
// 
//     spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
//     spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
//     spi_stop(); 
//     
//     // feel like i don't know what is going on here...some bitshifting
//     // presumes that temp_matrix[] is only 0 or 1; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
//     col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);
// 
//     return col_pin_state;
// }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // what if we try putting everything that needs the temp_matrix inside this function...
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);

        // uint16_t temp_col_state = read_all_cols();
        // if (temp_col_state != 0) {
            // printf("row (%d), col register data: %u \n", row, temp_col_state);
        // }

        uint16_t col_pin_state = 0;

        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
        spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t)); // receive(data, length) um like, data = the object to store the received data in?
        spi_stop(); 

        // feel like i don't know what is going on here...some bitshifting
        // presumes that the array temp_matrix[] is only 2 items; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
        col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);
        
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            // printf("row: %d \n", row);
            // 
            temp_matrix[current_col] |= (((col_pin_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        // for(int i = 0; i < MATRIX_COLS; i++) {
        //     printf(" %d ", temp_matrix[i]); // this outputs zeros
        // }
        // printf("sizeof matrix_row_t: %d \n", sizeof(matrix_row_t));
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
        // printf("Matrix of size %d has changed. \n", msize);
    }
    return matrix_has_changed;
}