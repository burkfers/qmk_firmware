
# Unicode support
UNICODE_COMMON = yes
UNICODE_ENABLE = yes


ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += keymaps/christrotter/rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif

ifeq ($(strip $(QUANTUM_PAINTER_ENABLED)), yes)
	SRC += keymaps/christrotter/ui.c
endif
