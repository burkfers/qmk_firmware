
ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += keymaps/christrotter/rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif

# QP_DEBUG_ENABLE = no		# degrades performance massively
# POINTING_DEBUG_ENABLE	= no
