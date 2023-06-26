#include "arcboard_mk17_tft.h"
#include "qp_st7789.h"
#include <qp.h>
#include <color.h>

bool lcd_power = false;
painter_device_t display;

void keyboard_post_init_kb(void) {
    display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
    qp_init(display, QP_ROTATION_0);
    qp_rect(display, 0, 0, 240, 320, HSV_BLACK, true);
    // print here
    wait_ms(50);
}

void housekeeping_task_kb(void) {
    // set the lcd_power state bool based on matrix activity vs. SCREEN_TIMEOUT value
    lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;
    setPinOutput(BACKLIGHT_PIN);
    if (lcd_power) {
        writePinHigh(BACKLIGHT_PIN);
        qp_power(display, true);
    } else {
        writePinLow(BACKLIGHT_PIN);
        qp_power(display, false);
    }
    if (lcd_power) {
        qp_rect(display, 0, 0, 240, 106, HSV_RED, true);
        qp_rect(display, 0, 106, 240, 212, HSV_GREEN, true);
        qp_rect(display, 0, 212, 240, 320, HSV_BLUE, true);
        // static uint32_t last_draw = 0;
        // if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        //     last_draw = timer_read32();
        //     // Draw 8px-wide rainbow filled rectangles down the left side of the display
        //     for (int i = 0; i < 319; i+=8) {
        //         qp_rect(display, 0, i, 7, i+7, i, 255, 255, true);
        //     }
        //     qp_flush(display);
        // }
    }
    if (qp_lvgl_attach(display)) {     // Attach LVGL to the display

    }
}

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void matrix_slave_scan_keymap(void);
