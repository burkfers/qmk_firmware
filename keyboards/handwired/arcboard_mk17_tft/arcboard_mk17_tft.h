#pragma once

#include "quantum.h"
#include QMK_KEYBOARD_H

#define LAYOUT( \
    RM_11, RM_12, \
    RM_21, RM_22 \
) \
{ \
    { RM_11, RM_12 }, \
    { RM_21, RM_22 }, \
}
