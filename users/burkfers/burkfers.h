#pragma once

#include "quantum.h"

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_GAME,
    LAYER_NUM,
    LAYER_NAV,
    LAYER_FUN,
    LAYER_MEDIA,
    LAYER_SYM,
    LAYER_POINTER,
};

enum my_keycodes {
    C_LT = SAFE_RANGE, // CUSTOM_LAYERTOGGLE
};

enum {
   U_TD_BOOT = 0,
   U_TD_CLR,
   U_TD_MAKER,
   U_TD_MAKEL,
   U_TD_SYSRQ,
};

#define DOTCOMM LT(10, KC_DOT)

void u_td_fn_boot(tap_dance_state_t *state, void *user_data);
void u_td_fn_make_l(tap_dance_state_t *state, void *user_data);
void u_td_fn_make_r(tap_dance_state_t *state, void *user_data);
void u_td_fn_sysrq_reisub(tap_dance_state_t *state, void *user_data);
void u_td_fn_clr(tap_dance_state_t *state, void *user_data);

#ifdef RGB_MATRIX_ENABLE
enum colors {
    hOFF = 0,
    hPRPL,
    hPINK,
    hCYAN,
    hLRED,
    hBLUE,
    hORNG,
    hRED,
    hMGTA,
    hYELO,
    hGREN,
};
extern const uint8_t PROGMEM ledmaps[][MATRIX_ROWS][MATRIX_COLS];
#endif
