ENCODER_MAP_ENABLE = yes
CONSOLE_ENABLE = yes
COMBO_ENABLE = yes

MACCEL_ENABLE = yes
VIA_ENABLE = yes

ifeq ($(strip $(MACCEL_ENABLE)), yes)
	SRC += ./maccel.c
	ifeq ($(strip $(VIA_ENABLE)), yes)
		SRC += ./maccel_via.c
	endif
	OPT_DEFS += -DMACCEL_ENABLE
endif
