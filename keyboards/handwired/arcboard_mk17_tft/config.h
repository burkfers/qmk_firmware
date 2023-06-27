// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// RP2040 reset functionality
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET              // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U  // Specify a optional status led which blinks when entering the bootloader

// RP2040 performance improvements
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

// SPI setup (PMW33xx is normally in use)
#define SPI_DRIVER SPID1  // Waveshare documentation says these pins are SPI1
#define SPI_SCK_PIN GP10  // clock is shared
#define SPI_MOSI_PIN GP11 // mosi is shared
#define SPI_MISO_PIN GP12 // this is dedicated for pmw according to wiring doc
#define DISPLAY_SPI_DIVISOR 4
#define DISPLAY_DC_PIN GP8
#define DISPLAY_CS_PIN GP9
#define DISPLAY_RST_PIN GP0 // setting this to NO_PIN causes the display to stop showing data
#define DISPLAY_LED_PIN GP22

// QP config
#define QUANTUM_PAINTER_TASK_THROTTLE 50 // trying to reduce the scan rate impact
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // this is super important - you get a white screen after 30s otherwise
