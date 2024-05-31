// Copyright 2024 burkfers (@burkfers)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

int8_t get_deadzone_inner(void);
void   set_deadzone_inner(int8_t idz);
int8_t get_deadzone_outer(void);
void   set_deadzone_outer(int8_t odz);
int8_t get_stick_angle(void);
void   set_stick_angle(int8_t angl);
void   step_stick_angle(int8_t step);
void   step_stick_mode(void);

enum ph_keycodes {
    PH_IDZ = QK_KB, // inner deadzone
    PH_ODZ,         // outer deadzone
    PH_ANGL,        // stick rotation angle
    PH_SMOD         // stick mode
};

enum ph_stick_modes {
    PH_SM_ANALOG, // stick mode: analog
    PH_SM_WASD,   // stick mode: wasd
    PH_SM_ARROWS, // stick mode: arrow keys
    PH_SM_END     // end marker
};

typedef struct joystick_axis_calibration {
    int16_t neutral;
    int16_t min;
    int16_t max;
} joystick_axis_calibration_t;

typedef struct joystick_calibration {
    joystick_axis_calibration_t x;
    joystick_axis_calibration_t y;
    uint8_t                     calibration_samples;
} joystick_calibration_t;

typedef struct {
    uint8_t mode;
    int8_t  deadzone_inner;
    int8_t  deadzone_outer;
    int16_t angle;
} ph_config_t;

void ph_handle_stick_keys_4(int8_t x, int8_t y, uint16_t u, uint16_t l, uint16_t d, uint16_t r);
void ph_handle_stick(joystick_calibration_t* stick);
void ph_read_stick(joystick_calibration_t* stick, int8_t* x, int8_t* y);
