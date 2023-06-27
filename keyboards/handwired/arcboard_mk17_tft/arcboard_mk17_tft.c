#include "arcboard_mk17_tft.h"
#include "qp_st7789.h"
#include <qp.h>
#include <color.h>
#include "print.h"

painter_device_t display;

void keyboard_post_init_kb(void) {
    display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
    qp_init(display, QP_ROTATION_0);
    // could not get the backlight feature working, sorry elpekenin!
    setPinOutput(DISPLAY_LED_PIN);
    writePinHigh(DISPLAY_LED_PIN);
    qp_rect(display, 0, 0, 240, 320, HSV_BLUE, true);
    qp_flush(display);
}

void housekeeping_task_kb(void) {
    // commenting the qp_rect out brings matrix scan rate from 25 to 12000

}
