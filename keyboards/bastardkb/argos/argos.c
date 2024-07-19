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
#    ifndef ARGOS_MINIMUM_DEFAULT_DPI
#        define ARGOS_MINIMUM_DEFAULT_DPI 300
#    endif // ARGOS_MINIMUM_DEFAULT_DPI

#    ifndef ARGOS_DEFAULT_DPI_CONFIG_STEP
#        define ARGOS_DEFAULT_DPI_CONFIG_STEP 100
#    endif // ARGOS_DEFAULT_DPI_CONFIG_STEP

#    ifndef ARGOS_MINIMUM_SNIPING_DPI
#        define ARGOS_MINIMUM_SNIPING_DPI 200
#    endif // ARGOS_MINIMUM_SNIPING_DPI

#    ifndef ARGOS_SNIPING_DPI_CONFIG_STEP
#        define ARGOS_SNIPING_DPI_CONFIG_STEP 100
#    endif // ARGOS_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.
#    ifndef ARGOS_DRAGSCROLL_DPI
#        define ARGOS_DRAGSCROLL_DPI 100
#    endif // ARGOS_DRAGSCROLL_DPI

#    ifndef ARGOS_DRAGSCROLL_BUFFER_SIZE
#        define ARGOS_DRAGSCROLL_BUFFER_SIZE 6
#    endif // !ARGOS_DRAGSCROLL_BUFFER_SIZE

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
    } __attribute__((packed));
} argos_config_t;

static argos_config_t g_argos_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_enabled` and `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void read_argos_config_from_eeprom(argos_config_t* config) {
    config->raw                   = eeconfig_read_kb() & 0xff;
    config->is_dragscroll_enabled = false;
    config->is_sniping_enabled    = false;
}

/**
 * \brief Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether drag-scroll
 * and/or sniper mode are enabled.  `read_argos_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void write_argos_config_to_eeprom(argos_config_t* config) {
    eeconfig_update_kb(config->raw);
}

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(argos_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * ARGOS_DEFAULT_DPI_CONFIG_STEP + ARGOS_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(argos_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * ARGOS_SNIPING_DPI_CONFIG_STEP + ARGOS_MINIMUM_SNIPING_DPI;
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(argos_config_t* config) {
    if (config->is_dragscroll_enabled) {
        pointing_device_set_cpi(ARGOS_DRAGSCROLL_DPI);
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
 * The increment/decrement steps are equal to ARGOS_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(argos_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to ARGOS_SNIPING_DPI_CONFIG_STEP.
 */
static void step_pointer_sniping_dpi(argos_config_t* config, bool forward) {
    config->pointer_sniping_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

uint16_t argos_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_argos_config);
}

uint16_t argos_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_argos_config);
}

void argos_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_argos_config, forward);
}

void argos_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_argos_config, forward);
    write_argos_config_to_eeprom(&g_argos_config);
}

void argos_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_argos_config, forward);
}

void argos_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_argos_config, forward);
    write_argos_config_to_eeprom(&g_argos_config);
}

bool argos_get_pointer_sniping_enabled(void) {
    return g_argos_config.is_sniping_enabled;
}

void argos_set_pointer_sniping_enabled(bool enable) {
    g_argos_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_argos_config);
}

bool argos_get_pointer_dragscroll_enabled(void) {
    return g_argos_config.is_dragscroll_enabled;
}

void argos_set_pointer_dragscroll_enabled(bool enable) {
    g_argos_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&g_argos_config);
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_argos_config);
    pointing_device_init_user();
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Implement drag-scroll.
 */
static void pointing_device_task_argos(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (g_argos_config.is_dragscroll_enabled) {
#    ifdef ARGOS_DRAGSCROLL_REVERSE_X
        scroll_buffer_x -= mouse_report->x;
#    else
        scroll_buffer_x += mouse_report->x;
#    endif // ARGOS_DRAGSCROLL_REVERSE_X
#    ifdef ARGOS_DRAGSCROLL_REVERSE_Y
        scroll_buffer_y -= mouse_report->y;
#    else
        scroll_buffer_y += mouse_report->y;
#    endif // ARGOS_DRAGSCROLL_REVERSE_Y
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > ARGOS_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > ARGOS_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // print("test 1");
    if (is_keyboard_master()) {
        // print("test 2");
        pointing_device_task_argos(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
    }
    return mouse_report;
}

#    if defined(POINTING_DEVICE_ENABLE) && !defined(NO_ARGOS_KEYCODES)
/** \brief Whether SHIFT mod is enabled. */
static bool has_shift_mod(void) {
#        ifdef NO_ACTION_ONESHOT
    return mod_config(get_mods()) & MOD_MASK_SHIFT;
#        else
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#        endif // NO_ACTION_ONESHOT
}
#    endif // POINTING_DEVICE_ENABLE && !NO_ARGOS_KEYCODES

/**
 * \brief Outputs the argos configuration to console.
 *
 * Prints the in-memory configuration structure to console, for debugging.
 * Includes:
 *   - raw value
 *   - drag-scroll: on/off
 *   - sniping: on/off
 *   - default DPI: internal table index/actual DPI
 *   - sniping DPI: internal table index/actual DPI
 */
static void debug_argos_config_to_console(argos_config_t* config) {
#    ifdef CONSOLE_ENABLE
    dprintf("(argos) process_record_kb: config = {\n"
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
        // debug_argos_config_to_console(&g_argos_config);
        return false;
    }
#    ifdef POINTING_DEVICE_ENABLE
#        ifndef NO_ARGOS_KEYCODES
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                argos_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                argos_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                argos_cycle_pointer_sniping_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                argos_cycle_pointer_sniping_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case SNIPING_MODE:
            argos_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                argos_set_pointer_sniping_enabled(!argos_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            argos_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                argos_set_pointer_dragscroll_enabled(!argos_get_pointer_dragscroll_enabled());
            }
            break;
    }
#        endif // !NO_ARGOS_KEYCODES
#    endif     // POINTING_DEVICE_ENABLE
    if (IS_QK_KB(keycode) || IS_MOUSEKEY(keycode)) {
        debug_argos_config_to_console(&g_argos_config);
    }
    return true;
}

void eeconfig_init_kb(void) {
    g_argos_config.raw                 = 0;
    g_argos_config.pointer_default_dpi = 4; // DPI=1000
    write_argos_config_to_eeprom(&g_argos_config);
    maybe_update_pointing_device_cpi(&g_argos_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_argos_config_from_eeprom(&g_argos_config);
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
    return true;
}
