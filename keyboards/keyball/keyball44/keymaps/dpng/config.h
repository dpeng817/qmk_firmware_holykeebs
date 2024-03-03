# pragma once

#undef MASTER_LEFT
#undef EE_HANDS
#define MASTER_RIGHT


#ifdef POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c
#define CIRQUE_PINNACLE_DIAMETER_MM 35
// Tap for left click.
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#endif