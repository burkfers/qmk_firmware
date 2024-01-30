# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

# project specific files
<<<<<<< HEAD
SRC =	drivers/led/issi/is31fl3736-simple.c \
=======
SRC =	drivers/led/issi/is31fl3736-mono.c \
>>>>>>> develop
		quantum/color.c \
		keyboards/wilba_tech/wt_mono_backlight.c \
		keyboards/wilba_tech/wt_main.c
I2C_DRIVER_REQUIRED = yes