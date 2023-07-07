
# Functionality options
TAP_DANCE_ENABLE        = yes

# LED settings
RGB_MATRIX_ENABLE 		= yes 		# matrix enable turns on the white background lighting
RGB_MATRIX_LEDMAPS_ENABLED = yes 	# turn on per-key colours

# Split settings
# RP2040-specific split options
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.
SERIAL_DRIVER = vendor

DRAGSCROLL_ENABLE		= yes

# Encoder
ENCODER_MAP_ENABLE = yes

# Enable the TFT screens
# currently disabled cuz wiring woes
QUANTUM_PAINTER_ENABLE 	= yes
