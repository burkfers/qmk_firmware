/**
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "argos.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#    ifndef DILEMMA_MINIMUM_DEFAULT_DPI
#        define DILEMMA_MINIMUM_DEFAULT_DPI 300
#    endif // DILEMMA_MINIMUM_DEFAULT_DPI

#    ifndef DILEMMA_DEFAULT_DPI_CONFIG_STEP
#        define DILEMMA_DEFAULT_DPI_CONFIG_STEP 100
#    endif // DILEMMA_DEFAULT_DPI_CONFIG_STEP

#    ifndef DILEMMA_MINIMUM_SNIPING_DPI
#        define DILEMMA_MINIMUM_SNIPING_DPI 200
#    endif // DILEMMA_MINIMUM_SNIPING_DPI

#    ifndef DILEMMA_SNIPING_DPI_CONFIG_STEP
#        define DILEMMA_SNIPING_DPI_CONFIG_STEP 100
#    endif // DILEMMA_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.
#    ifndef DILEMMA_DRAGSCROLL_DPI
#        define DILEMMA_DRAGSCROLL_DPI 100
#    endif // DILEMMA_DRAGSCROLL_DPI

#    ifndef DILEMMA_DRAGSCROLL_BUFFER_SIZE
#        define DILEMMA_DRAGSCROLL_BUFFER_SIZE 6
#    endif // !DILEMMA_DRAGSCROLL_BUFFER_SIZE

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
    } __attribute__((packed));
} dilemma_config_t;

static dilemma_config_t g_dilemma_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_enabled` and `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void read_dilemma_config_from_eeprom(dilemma_config_t* config) {
    config->raw                   = eeconfig_read_kb() & 0xff;
    config->is_dragscroll_enabled = false;
    config->is_sniping_enabled    = false;
}

/**
 * \brief Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether drag-scroll
 * and/or sniper mode are enabled.  `read_dilemma_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void write_dilemma_config_to_eeprom(dilemma_config_t* config) {
    eeconfig_update_kb(config->raw);
}

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(dilemma_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * DILEMMA_DEFAULT_DPI_CONFIG_STEP + DILEMMA_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(dilemma_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * DILEMMA_SNIPING_DPI_CONFIG_STEP + DILEMMA_MINIMUM_SNIPING_DPI;
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(dilemma_config_t* config) {
    if (config->is_dragscroll_enabled) {
        pointing_device_set_cpi(DILEMMA_DRAGSCROLL_DPI);
    } else if (config->is_sniping_enabled) {
        pointing_device_set_cpi(get_pointer_sniping_dpi(config));
    } else {
        pointing_device_set_cpi(get_pointer_default_dpi(config));
    }
}

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to DILEMMA_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(dilemma_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to DILEMMA_SNIPING_DPI_CONFIG_STEP.
 */
static void step_pointer_sniping_dpi(dilemma_config_t* config, bool forward) {
    config->pointer_sniping_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

uint16_t dilemma_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_dilemma_config);
}

uint16_t dilemma_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_dilemma_config);
}

void dilemma_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_dilemma_config, forward);
}

void dilemma_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_dilemma_config, forward);
    write_dilemma_config_to_eeprom(&g_dilemma_config);
}

void dilemma_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_dilemma_config, forward);
}

void dilemma_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_dilemma_config, forward);
    write_dilemma_config_to_eeprom(&g_dilemma_config);
}

bool dilemma_get_pointer_sniping_enabled(void) {
    return g_dilemma_config.is_sniping_enabled;
}

void dilemma_set_pointer_sniping_enabled(bool enable) {
    g_dilemma_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_dilemma_config);
}

bool dilemma_get_pointer_dragscroll_enabled(void) {
    return g_dilemma_config.is_dragscroll_enabled;
}

void dilemma_set_pointer_dragscroll_enabled(bool enable) {
    g_dilemma_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&g_dilemma_config);
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_dilemma_config);
    pointing_device_init_user();
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Implement drag-scroll.
 */
static void pointing_device_task_dilemma(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (g_dilemma_config.is_dragscroll_enabled) {
#    ifdef DILEMMA_DRAGSCROLL_REVERSE_X
        scroll_buffer_x -= mouse_report->x;
#    else
        scroll_buffer_x += mouse_report->x;
#    endif // DILEMMA_DRAGSCROLL_REVERSE_X
#    ifdef DILEMMA_DRAGSCROLL_REVERSE_Y
        scroll_buffer_y -= mouse_report->y;
#    else
        scroll_buffer_y += mouse_report->y;
#    endif // DILEMMA_DRAGSCROLL_REVERSE_Y
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > DILEMMA_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > DILEMMA_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // print("test 1");
    if (is_keyboard_master()) {
        // print("test 2");
        pointing_device_task_dilemma(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
    }
    return mouse_report;
}

#    if defined(POINTING_DEVICE_ENABLE) && !defined(NO_DILEMMA_KEYCODES)
/** \brief Whether SHIFT mod is enabled. */
static bool has_shift_mod(void) {
#        ifdef NO_ACTION_ONESHOT
    return mod_config(get_mods()) & MOD_MASK_SHIFT;
#        else
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#        endif // NO_ACTION_ONESHOT
}
#    endif // POINTING_DEVICE_ENABLE && !NO_DILEMMA_KEYCODES

/**
 * \brief Outputs the Dilemma configuration to console.
 *
 * Prints the in-memory configuration structure to console, for debugging.
 * Includes:
 *   - raw value
 *   - drag-scroll: on/off
 *   - sniping: on/off
 *   - default DPI: internal table index/actual DPI
 *   - sniping DPI: internal table index/actual DPI
 */
static void debug_dilemma_config_to_console(dilemma_config_t* config) {
#    ifdef CONSOLE_ENABLE
    dprintf("(dilemma) process_record_kb: config = {\n"
            "\traw = 0x%X,\n"
            "\t{\n"
            "\t\tis_dragscroll_enabled=%u\n"
            "\t\tis_sniping_enabled=%u\n"
            "\t\tdefault_dpi=0x%X (%u)\n"
            "\t\tsniping_dpi=0x%X (%u)\n"
            "\t}\n"
            "}\n",
            config->raw, config->is_dragscroll_enabled, config->is_sniping_enabled, config->pointer_default_dpi, get_pointer_default_dpi(config), config->pointer_sniping_dpi, get_pointer_sniping_dpi(config));
#    endif // CONSOLE_ENABLE
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        debug_dilemma_config_to_console(&g_dilemma_config);
        return false;
    }
#    ifdef POINTING_DEVICE_ENABLE
#        ifndef NO_DILEMMA_KEYCODES
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                dilemma_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                dilemma_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                dilemma_cycle_pointer_sniping_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                dilemma_cycle_pointer_sniping_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case SNIPING_MODE:
            dilemma_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                dilemma_set_pointer_sniping_enabled(!dilemma_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            dilemma_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                dilemma_set_pointer_dragscroll_enabled(!dilemma_get_pointer_dragscroll_enabled());
            }
            break;
    }
#        endif // !NO_DILEMMA_KEYCODES
#    endif     // POINTING_DEVICE_ENABLE
    debug_dilemma_config_to_console(&g_dilemma_config);
    if (IS_QK_KB(keycode) || IS_MOUSEKEY(keycode)) {
        debug_dilemma_config_to_console(&g_dilemma_config);
    }
    return true;
}

void eeconfig_init_kb(void) {
    g_dilemma_config.raw                 = 0;
    g_dilemma_config.pointer_default_dpi = 3; // DPI=1000
    write_dilemma_config_to_eeprom(&g_dilemma_config);
    maybe_update_pointing_device_cpi(&g_dilemma_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_dilemma_config_from_eeprom(&g_dilemma_config);
    matrix_init_user();
}
#endif // POINTING_DEVICE_ENABLE

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void keyboard_pre_init_kb(void) {
    // Ensures that GP26 through GP29 are initialized as digital inputs (as
    // opposed to analog inputs).  These GPIOs are shared with A0 through A3,
    // respectively.  On RP2040-B2 and later, the digital inputs are disabled by
    // default (see RP2040-E6).
    gpio_init(GP26);
    gpio_init(GP27);
    gpio_init(GP28);
    gpio_init(GP29);

    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_update_pwm_buffers(void);
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
    return true;
}

/**
 * LEDs index.
 *
 *  0 - 17 Underglow                36 - 53 Underglow
 * ╭────────────────────╮         ╭────────────────────╮
 *   22  21  20  19  18             54  55  56  57  58
 * ├────────────────────┤         ├────────────────────┤
 *   23  24  25  26  27             63  62  61  60  59
 * ├────────────────────┤         ├────────────────────┤
 *   32  31  30  29  28             64  65  66  67  68
 * ╰────────────────────╯         ╰────────────────────╯
 *               33  34  35     71  70  69
 *             ╰────────────╯ ╰────────────╯
 */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {     22,     21,     20,     19,     18 }, // Top row
    {     23,     24,     25,     26,     27 }, // Middle row
    {     32,     31,     30,     29,     28 }, // Bottom row
    {     34,     35,     33, NO_LED, NO_LED }, // Thumb cluster
    // Right split.
    {     58,     57,     56,     55,     54 }, // Top row
    {     59,     60,     61,     62,     63 }, // Middle row
    {     68,     67,     66,     65,     64 }, // Bottom row
    {     70,     71,     69, NO_LED, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split underglow.
    /* index=0  */ {  82,   0 }, {  60,   0 }, {  22,   0 }, {  15,   0 }, // Top 4
    /* index=4  */ {   0,  25 }, {   0,  40 }, {   0,  55 },               // Pinky edge 3
    /* index=7  */ {  15,  45 }, {  30,  45 }, {  35,  60 }, {  55,  62 }, // Bottom 8
    /* index=11 */ {  72,  64 }, {  90,  64 }, {  98,  47 }, { 107,  40 },
    /* index=15 */ { 110,  33 }, { 110,  19 }, { 110,   5 },               // Inner edge 3
    // Left split per-key.
    /* index=18 */ {  73,  11 }, {  56,   9 }, {  39,   5 }, {  22,  10 }, {   5,  15 }, // row 1 (left most) 90, 107
    /* index=23 */ {   5,  30 }, {  22,  25 }, {  39,  20 }, {  56,  24 }, {  73,  26 }, // row 2 (middle)
    /* index=28 */ {  73,  41 }, {  56,  39 }, {  39,  35 }, {  22,  25 }, {   5,  45 }, // row 3 (left most)
    /* index=33 */ {  45,  51 }, {  64,  53 }, {  81,  60 }, // Thumb cluster
    // Right split underglow.
    /* index=36 */ { 142,   0 }, { 164,   0 }, { 202,   0 }, { 209,   0 }, // Top 4
    /* index=40 */ { 224,  25 }, { 224,  40 }, { 224,  55 },               // Pinky edge 3
    /* index=43 */ { 209,  45 }, { 194,  45 }, { 189,  60 }, { 169,  62 }, // Bottom 8
    /* index=47 */ { 152,  64 }, { 134,  64 }, { 126,  47 }, { 117,  40 },
    /* index=51 */ { 114,  33 }, { 114,  19 }, { 114,   5 },               // Inner edge 3
    // Right split per-key.
    /* index=54 */ { 151,  11 }, { 168,   9 }, { 185,   5 }, { 202,  10 }, { 219,  15 }, // row 1 (right most) 117 134
    /* index=59 */ { 219,  30 }, { 202,  25 }, { 185,  20 }, { 168,  24 }, { 151,  26 }, // row 2 (middle)
    /* index=64 */ { 151,  41 }, { 168,  39 }, { 185,  35 }, { 202,  25 }, { 219,  45 }, // row 3 (right most)
    /* index=69 */ { 179,  51 }, { 160,  53 }, { 143,  60 }, // Thumb cluster
}, {
    /* LED index to flag. */
    // Left split underglow.
    /* index=0  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=3  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=6  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=9  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=12 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=15 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    // Left split per-key.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split underglow.
    /* index=36 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=39 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=42 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=45 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=48 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=51 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    // Right split per-key.
    /* index=54 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=57 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=60 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=63 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=66 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=69 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
} };
#endif
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (index) {
        case 0: // Left-half encoder, mouse scroll.
            tap_code(clockwise ? KC_MS_WH_UP : KC_MS_WH_DOWN);
            break;
        case 1: // Right-half encoder, volume control.
            tap_code(clockwise ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
            break;
    }
    return true;
}
#endif // ENCODER_ENABLE
