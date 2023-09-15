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

