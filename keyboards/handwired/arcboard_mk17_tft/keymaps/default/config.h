#pragma once

#define DEBUG_MATRIX_SCAN_RATE
// #define QUANTUM_PAINTER_DEBUG

#if defined(POINTING_DEVICE_ENABLE)
    #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
    #define AUTO_MOUSE_DEFAULT_LAYER 1
    #define AUTO_MOUSE_DEBOUNCE 25
    // #define POINTING_DEVICE_INVERT_X_RIGHT
    #define POINTING_DEVICE_INVERT_Y_RIGHT
    #define ROTATIONAL_TRANSFORM_ANGLE 0
    #define DRAGSCROLL_BUFFER_SIZE 6
    // #define POINTING_DEVICE_INVERT_X
    // #define POINTING_DEVICE_ROTATION_90_RIGHT
    // #define POINTING_DEVICE_ROTATION_90
    // #define POINTING_DEVICE_INVERT_X            // Inverted movement for X (not sure why this is set tbh...maybe due to the kb half it's installed on?)
    // #define POINTING_DEVICE_INVERT_Y
    // #define DRAGSCROLL_REVERSE_X                // i must have installed the sensor flipped around
    // CPI not being set correctly...hmm...
    #define RIGHT_PMW_CPI 500       // your mouse cpi (DPI) setting (how fast the ball tracks)
    #define LEFT_PMW_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
#endif
