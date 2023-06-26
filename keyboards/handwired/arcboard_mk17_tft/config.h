// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// setting the SPI pins for the PMW // why isn't this inside pointing_device_enable?
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10  // clock is shared
#define SPI_MOSI_PIN GP11 // mosi is shared....?
#define SPI_MISO_PIN GP12 // this is dedicated for pmw according to wiring doc

// RP2040 reset functionality
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET      // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

// For the tft display
#define SPI_MATRIX_DIVISOR 8
#define DISPLAY_SPI_DIVISOR 4
#define DISPLAY_DC_PIN GP8
#define DISPLAY_CS_PIN GP9
#define DISPLAY_RST_PIN GP0 // NO_PIN // not needed for 7789
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // never turn off the display; i'm troubleshooting why QP is not working, this is not really necessary
#define QUANTUM_PAINTER_TASK_THROTTLE 10 // trying to reduce the scan rate hit
#define QP_MATRIX_SCAN_INTERVAL 1000
#define BACKLIGHT_PIN GP22
