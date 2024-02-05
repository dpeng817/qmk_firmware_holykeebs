#pragma once

#undef MASTER_LEFT
#undef EE_HANDS
#undef MASTER_RIGHT

#define SERIAL_USART_TX_PIN GP1

// The right hand with the thumb trackball is master here.
#define MASTER_RIGHT


// #define PERMISSIVE_HOLD

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Configuration for dual trackballs.
// Left side can only go in this configuration.
#define POINTING_DEVICE_ROTATION_270
// Right side rotation on this keyboard is outer thumb.
#define POINTING_DEVICE_ROTATION_270_RIGHT

// #if defined(PS2_DRIVER_BUSYWAIT) || defined(PS2_DRIVER_INTERRUPT)
// #define PS2_MOUSE_INVERT_X
// #define PS2_MOUSE_INVERT_Y

// #define PS2_CLOCK_PIN   D3
// #define PS2_DATA_PIN    B4

// #define PS2_MOUSE_USE_REMOTE_MODE
// #endif

/* #ifdef PS2_DRIVER_INTERRUPT
// #define PS2_INT_INIT()  do {    \
//     EICRA |= ((1<<ISC31) |      \
//               (0<<ISC30));      \
// } while (0)
// #define PS2_INT_ON()  do {      \
//     EIMSK |= (1<<INT3);         \
// } while (0)
// #define PS2_INT_OFF() do {      \
//     EIMSK &= ~(1<<INT3);        \
// } while (0)
// #define PS2_INT_VECT   INT3_vect
// #endif */