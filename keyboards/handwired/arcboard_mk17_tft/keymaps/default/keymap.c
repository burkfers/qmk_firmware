// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "arcboard_mk17_tft.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
    MO(_MOUSE), MO(_MOUSE)
),
[_MOUSE] = LAYOUT(
    KC_TRNS, KC_TRNS
),
[_SYMBOLS] = LAYOUT(
    KC_TRNS, KC_TRNS
),
[_NAV] = LAYOUT(
    KC_TRNS, KC_TRNS
)
};

void keyboard_post_init_user(void) {
  debug_enable=true;
}

#if defined(ENCODER_MAP_ENABLE)
    #include "encoder_maps.c"
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #include "pointing.c"
#endif

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
            case _MOUSE:
                return "mouse";
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
            const char        *mouse = "mouse";
            int ypos = 150;
            snprintf(buf, sizeof(buf), "%s", layer_name);
            int qwerty_layer = strcmp(layer_name, qwerty);
            int mouse_layer = strcmp(layer_name, mouse);
            if (qwerty_layer==0) {
                qp_rect(display, 0, 106, 240, 212, HSV_WHITE, true);
                qp_drawtext_recolor(display, 35, ypos, font, "QWERTY", HSV_BLACK, HSV_WHITE);
            }
            if (mouse_layer==0) {
                qp_rect(display, 0, 106, 240, 212, HSV_BLUE, true);
                qp_drawtext_recolor(display, 45, ypos, font, "MOUSE", HSV_WHITE, HSV_BLUE);
            }
        }
        qp_flush(display);
    }

void housekeeping_task_user(void) {
    draw_ui_user();
}
#endif // QUANTUM_PAINTER_ENABLE

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    __attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
    #include "rgb_ledmaps.h"
#endif
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
        #if defined(RGB_MATRIX_LEDMAPS_ENABLED)
            && process_record_user_rgb_matrix(keycode, record)
        #endif
        #if defined(CUSTOM_POINTING_DEVICE)
            && process_record_pointing(keycode, record)
        #endif
          && true)) {
        return false;
    }
    #if defined(DRAGSCROLL_ENABLE)
        if (keycode == DRAG_SCROLL && record->event.pressed) {
            set_scrolling = !set_scrolling;
            uprintf("Scrolling bool: %s \n", set_scrolling ? "true" : "false");
        }
    #endif
    return true;
}

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.

// Right thumb: KC_MULTILNE, OSM(MOD_LSFT), MO(_SYMBOLS), KC_ENTER, KC_SPACE, MAGIPLAY,
const ledmap ledmaps[] = {
    [_QWERTY]   = LEDMAP(
      CYAN, BLUE
   ),
   [_MOUSE]     = LEDMAP(
      RED, PURPLE
   ),
    [_SYMBOLS]   = LEDMAP(
      CYAN, BLUE
   ),
   [_NAV]     = LEDMAP(
      RED, PURPLE
   )
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

