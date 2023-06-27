// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "arcboard_mk17_tft.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

void keyboard_post_init_user(void) {
  debug_enable=true;
}

#if defined(QUANTUM_PAINTER_ENABLE)
    #include "qp_st7789.h"
    #include <qp.h>
    #include "graphics/futura40.qff.c"
    #include "color.h"
    static painter_font_handle_t font;
    static painter_device_t display;
    const char *current_layer_name(void) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                return "qwerty";
        }
        return "unknown";
    }

    void init_ui(void) {
        font = qp_load_font_mem(font_futura40);
        display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
        qp_init(display, QP_ROTATION_0);
        // could not get the backlight feature working, sorry elpekenin!
        setPinOutput(DISPLAY_LED_PIN);
        writePinHigh(DISPLAY_LED_PIN);
        painter_font_handle_t font;
        font = qp_load_font_mem(font_futura40);
        qp_rect(display, 0, 0, 240, 320, HSV_BLUE, true);
        qp_drawtext_recolor(display, 25, 25, font, "Init...", HSV_WHITE, HSV_BLUE);
        qp_flush(display);
    }

    void draw_ui_user(void) {
        uint16_t width;
        uint16_t height;
        qp_get_geometry(display, &width, &height, NULL, NULL, NULL);
        char buf[32] = {0};
        bool layer_state_redraw = false;
        static uint32_t last_layer_state   = 0;
        if (last_layer_state  != layer_state) {
            last_layer_state   = layer_state;
            layer_state_redraw = true;
        }
        if (layer_state_redraw) {
            extern const char *current_layer_name(void);
            const char        *layer_name = current_layer_name();
            const char        *qwerty = "qwerty";
            int ypos = 150;
            snprintf(buf, sizeof(buf), "%s", layer_name);
            int qwerty_layer = strcmp(layer_name, qwerty);
            if (qwerty_layer==0) {
                qp_rect(display, 0, 106, 240, 212, HSV_WHITE, true);
                qp_drawtext_recolor(display, 35, ypos, font, "QWERTY", HSV_BLACK, HSV_WHITE);
            }
        }
        qp_flush(display);
    }

void housekeeping_task_user(void) {
    draw_ui_user();
}

#endif // QUANTUM_PAINTER_ENABLE
