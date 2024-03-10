# Config for my custom keyball44 which has a trackball on the right, and a cirque trackpad on the left.
SERIAL_DRIVER = vendor
CONSOLE_ENABLE = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

POINTING_DEVICE_ENABLE = yes
OPT_DEFS += -DSPLIT_POINTING_ENABLE
OPT_DEFS += -DPOINTING_DEVICE_COMBINED
# My ill fated attempt to gttet the trackpad to work. Leaving it here as comment for future reference if I decide to come back to it.

# # If on the left side, the driver is cirque_pinnacle_i2c
# ifeq ($(strip $(SIDE)), left)
# 	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
# else
# 	POINTING_DEVICE_DRIVER = custom
# endif
POINTING_DEVICE_DRIVER = custom

MOUSEKEY_ENABLE = yes
	