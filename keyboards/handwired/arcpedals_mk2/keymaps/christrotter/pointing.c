// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcpedals_mk2.h"
#include "keymap.h"
#include "print.h"

#if defined(POINTING_DEVICE_ENABLE)
    report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
        int8_t x = 0;
        int8_t y = 0;
        x = mouse_report.x;
        y = mouse_report.y;
        // uprintf("x: %d, y: %d",x,y);
        if (x > 100) {
            layer_move(0);
            // uprintf("Move to 0.");
        } else if (x < -100) {
            layer_move(1);
            // uprintf("Move to 1.");
        }
        if (y > 100) {
            layer_move(2);
            // uprintf("Move to 2.");
        } else if (y < -100) {
            layer_move(3);
            // uprintf("Move to 3.");
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
        return mouse_report;
    }
#endif
