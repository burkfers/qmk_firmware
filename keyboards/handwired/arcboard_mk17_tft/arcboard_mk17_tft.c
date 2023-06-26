#include "arcboard_mk17_tft.h"
#include "qp_st7789.h"
#include <qp.h>
#include <color.h>
#include "print.h"

painter_device_t display;

void keyboard_post_init_kb(void) {
    display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
    qp_init(display, QP_ROTATION_0);
    // could not get the backlight feature working
    setPinOutput(BACKLIGHT_PIN);
    writePinHigh(BACKLIGHT_PIN);
    wait_ms(50);
    // don't think this matters to my situation, but here it is...
    qp_power(display, true);
}

void housekeeping_task_kb(void) {
        qp_rect(display, 0, 0, 240, 106, HSV_RED, true);
        qp_rect(display, 0, 106, 240, 212, HSV_GREEN, true);
        qp_rect(display, 0, 212, 240, 320, HSV_BLUE, true);
}
