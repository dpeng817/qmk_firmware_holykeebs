SERIAL_DRIVER = vendor


# Disable things we don't support that take up unnecessary space.
RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

# Options for which trackball position we're configuring: left or outer thumb
ifeq ($(strip $(POINTING_DEVICE_POSITION)), left)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_LEFT
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb_outer)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB_OUTER
endif

OPT_DEFS += -DSPLIT_POINTING_ENABLE
OPT_DEFS += -DPOINTING_DEVICE_COMBINED

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball

# Enable rainbow trackball config
# SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c

MOUSEKEY_ENABLE = yes

OLED_ENABLE     = no
PIMORONI_TRACKBALL_SCALE = 0.001
