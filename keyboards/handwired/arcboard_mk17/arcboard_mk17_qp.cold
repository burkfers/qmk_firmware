// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif
#include "arcboard_mk17_qp.h"
#include <qp.h>
#include <qp_st7789.h>

painter_device_t display;

void ui_init(void) {
    display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
    // cuz of mirroring STLs, one side has a flipped tft
    if (is_keyboard_left()) {
        qp_init(display, QP_ROTATION_180);
    }
    else {
        qp_init(display, QP_ROTATION_0);
    }
    qp_power(display, true);
    qp_clear(display);
    for (int i = 0; i < 239; i+=8) {
        qp_rect(display, 0, i, 7, i+7, i, 255, 255, true);
    }
    qp_flush(display);
}

void draw_ui_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 8px-wide rainbow filled rectangles down the left side of the display
        for (int i = 0; i < 239; i+=8) {
            qp_rect(display, 0, i, 7, i+7, i, 255, 255, true);
        }
        qp_flush(display);
    }
}
