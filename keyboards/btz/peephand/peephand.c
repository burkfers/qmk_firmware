// Copyright 2024 burkfers (@burkfers)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "peephand.h"
#include "analog.h"
#include <math.h>

_Static_assert(sizeof(ph_config_t) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");


#define STICK_TIMER 5 // polling/handling interval (ms)
#define NUM_CALIBRATION_SAMPLES 10
#define INNER_DEADZONE 60
#define OUTER_DEADZONE 60
#define STICK_ANGLE -110

#define CLAMP(val, min, max) (val < min ? min : (val > max ? max : val))
#define PROJECT(val, rmin, rmax, tmin, tmax) CLAMP((((float)(val - rmin) / (float)(rmax - rmin)) * (float)(tmax - tmin)) + tmin, tmin, tmax)

static joystick_calibration_t phs;
static uint32_t               peephand_stick_timer;
static ph_config_t            ph_config;

void housekeeping_task_kb(void) {
    if (timer_elapsed(peephand_stick_timer) > STICK_TIMER) {
        ph_handle_stick(&phs);
        peephand_stick_timer = timer_read32();
    }
}

void set_deadzone_inner(int8_t idz) {
    ph_config.deadzone_inner = idz;
    eeconfig_update_kb_datablock(&ph_config);
}
int8_t get_deadzone_inner() {
    return ph_config.deadzone_inner;
}
void set_deadzone_outer(int8_t odz) {
    ph_config.deadzone_outer = odz;
    eeconfig_update_kb_datablock(&ph_config);
}
int8_t get_deadzone_outer() {
    return ph_config.deadzone_outer;
}
int8_t get_stick_angle() {
    return ph_config.angle;
}
void set_stick_angle(int8_t angl) {
    ph_config.angle = angl;
    eeconfig_update_kb_datablock(&ph_config);
}
void step_stick_angle(int8_t step) {
    set_stick_angle(get_stick_angle() + step);
    dprintf("stick angle now %i\n", get_stick_angle());
}
void step_stick_mode() {
    joystick_set_axis(0, 0);
    joystick_set_axis(1, 0);

    ph_config.mode += 1;
    if (ph_config.mode >= PH_SM_END) ph_config.mode = 0;
    dprintf("Stick mode now %i\n", ph_config.mode);
}

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL};

void ph_handle_stick(joystick_calibration_t* stick) {
    int8_t x = 0;
    int8_t y = 0;

    ph_read_stick(stick, &x, &y);

    switch (ph_config.mode) {
        case PH_SM_ANALOG:
            joystick_set_axis(0, x);
            joystick_set_axis(1, y);
            break;
        case PH_SM_WASD:
            ph_handle_stick_keys_4(x, y, KC_W, KC_A, KC_S, KC_D);
            break;
        case PH_SM_ARROWS:
            ph_handle_stick_keys_4(x, y, KC_UP, KC_LEFT, KC_DOWN, KC_RGHT);
            break;
    }
}

void ph_handle_stick_keys_4(int8_t x, int8_t y, uint16_t u, uint16_t l, uint16_t d, uint16_t r) {
    static int8_t px;
    static int8_t py;

    const int8_t actuation_point = 60;

    if (y > actuation_point && py <= actuation_point) {
        register_code16(d);
        dprintf("registering d\n");
    } else if (y <= actuation_point && py > actuation_point) {
        unregister_code16(d);
        dprintf("unregistering d\n");
    }
    if (y < -1*actuation_point && py >= -1*actuation_point) {
        register_code16(u);
        dprintf("registering u\n");
    } else if (y >= -1*actuation_point && py < -1*actuation_point) {
        unregister_code16(u);
        dprintf("unregistering u\n");
    }
    if (x > actuation_point && px <= actuation_point) {
        register_code16(r);
        dprintf("registering r\n");
    } else if (x <= actuation_point && px > actuation_point) {
        unregister_code16(r);
        dprintf("unregistering r\n");
    }
    if (x < -1*actuation_point && px >= -1*actuation_point) {
        register_code16(l);
        dprintf("registering l\n");
    } else if (x >= -1*actuation_point && px < -1*actuation_point) {
        unregister_code16(l);
        dprintf("unregistering l\n");
    }

    px = x;
    py = y;
}

void ph_read_stick(joystick_calibration_t* stick, int8_t* outx, int8_t* outy) {
    const int16_t rawx = analogReadPin(GP28);
    const int16_t rawy = analogReadPin(GP29);

    // find neutral - hacky, but I don't want to store many samples for an avg
    if (stick->calibration_samples > 0) {
        if (stick->x.neutral == 0)
            stick->x.neutral = rawx;
        else
            stick->x.neutral = (stick->x.neutral + rawx) / 2;

        if (stick->y.neutral == 0)
            stick->y.neutral = rawy;
        else
            stick->y.neutral = (stick->y.neutral + rawy) / 2;

        stick->calibration_samples -= 1;
    }

    // get x/y
    int16_t x = rawx - stick->x.neutral;
    int16_t y = rawy - stick->y.neutral;

    // recalibrate min/maximums
    if (x < stick->x.min) stick->x.min = x;
    if (x > stick->x.max) stick->x.max = x;
    if (y < stick->y.min) stick->y.min = y;
    if (y > stick->y.max) stick->y.max = y;

    if (abs(x) < INNER_DEADZONE) x = 0;
    if (abs(y) < INNER_DEADZONE) y = 0;

    int8_t scalex;
    int8_t scaley;
    if (x > 0)
        scalex = PROJECT(x, 0, stick->x.max - OUTER_DEADZONE, 0, 127);
    else if (x < 0)
        scalex = PROJECT(x, stick->x.min - OUTER_DEADZONE, 0, -127, 0);
    else
        scalex = 0;

    if (y > 0)
        scaley = PROJECT(y, 0, stick->y.max - OUTER_DEADZONE, 0, 127);
    else if (y < 0)
        scaley = PROJECT(y, stick->y.min - OUTER_DEADZONE, 0, -127, 0);
    else
        scaley = 0;

    // rotation time
    double theta = (double)ph_config.angle * M_PI / 180.0f;
    *outx        = CLAMP(((double)scalex * cos(theta)) + ((double)scaley * sin(theta)), -127, 127);
    *outy        = CLAMP((-1 * (double)scalex * sin(theta)) + ((double)scaley * cos(theta)), -127, 127);
}

void keyboard_post_init_kb() {
    phs.calibration_samples = NUM_CALIBRATION_SAMPLES;

    eeconfig_read_kb_datablock(&ph_config);

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) return false;

    bool shifted;

    switch (keycode) {
        case PH_IDZ:
            if (record->event.pressed) {
                shifted = get_mods() & MOD_MASK_SHIFT;
                set_deadzone_inner(get_deadzone_inner() + (shifted ? -1 : 1));
            }
            return false;
        case PH_ODZ:
            if (record->event.pressed) {
                shifted = get_mods() & MOD_MASK_SHIFT;
                set_deadzone_outer(get_deadzone_outer() + (shifted ? -1 : 1));
            }
            return false;
        case PH_ANGL:
            if (record->event.pressed) {
                shifted = get_mods() & MOD_MASK_SHIFT;
                step_stick_angle(shifted ? -5 : 5);
            }
            return false;
        case PH_SMOD:
            if (record->event.pressed) {
                step_stick_mode();
            }
            return false;
        default:
            return true;
    }
}

void eeconfig_init_kb() {
    ph_config.deadzone_inner = INNER_DEADZONE;
    ph_config.deadzone_outer = OUTER_DEADZONE;
    ph_config.angle          = STICK_ANGLE;
    ph_config.mode           = PH_SM_WASD;
    eeconfig_update_kb_datablock(&ph_config);

    eeconfig_init_user();
}
