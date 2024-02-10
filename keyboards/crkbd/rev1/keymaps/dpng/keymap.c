#include "action.h"
#include "math.h"
#include "dpng.h"
#include <time.h>

#include QMK_KEYBOARD_H


enum custom_keycodes {
  M_ALFRED = SAFE_RANGE, // Opens alfred in arc mode
  M_HMRW, // Opens homerow
  M_SCRSHT, // Activates screenshot mode on mac
  M_SWITCH_MOUSE, // Switches mouse behavior
  B_MOUSE, // Mouse left click on tap, right click on hold
};

// For mouse switching behavior
bool mouse_switch = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case B_MOUSE:
      // can't get mod tap to work for now. Just use tap code for now.
      if(record->event.pressed) {
        tap_code16(KC_BTN1);
      }  
      // if(record->tap.count && record->event.pressed) {
      //   tap_code16(KC_BTN1);
      // } 
      // else if (record->event.pressed) {
      //   tap_code16(KC_BTN2);
      // }
      return false;
    // opens alfred in arc mode
    case M_ALFRED:
      if (record->event.pressed) {
        // Sequence is cmd space (delay 50) space
        SEND_STRING(SS_LGUI(" ") SS_DELAY(50) SS_TAP(X_SPC));
      }
      return false;
    // activates homerow
    case M_HMRW:
      if (record->event.pressed) {
        // Sequence is cmd shift s
        SEND_STRING(SS_LGUI(SS_LSFT("s")));
      }
      return false;
    // activates mac screenshot mode
    case M_SCRSHT:
      if (record->event.pressed) {
        // Sequence is cmd shift 4
        SEND_STRING(SS_LGUI(SS_LSFT("4")));
      }
      return false;
    case M_SWITCH_MOUSE:
      if (record->event.pressed) {
        mouse_switch = !mouse_switch;
      }
      return true;
  }
  return true;
}

// Organization is 6 keys per row, thumb cluster has 3 keys on left and 2 keys on right (a gap is left for the trackball on the right thumb).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Regular keys
  [0] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_Q,       KC_W,       KC_E,       KC_R,        KC_T,                KC_Y,     KC_U,       KC_I,       KC_O,      KC_P,     KC_BSPC,
    KC_ESC,    KC_A,       KC_S,       KC_D,       MT(MOD_LGUI, KC_F),        KC_G,                KC_H,     KC_J,       KC_K,       KC_L,      KC_SCLN,  KC_QUOT,
    KC_LSFT,   KC_Z,       KC_X,       KC_C,       KC_V,        KC_B,                KC_N,     KC_M,       KC_COMM,    KC_DOT,    KC_SLSH,  KC_ENTER,
                                       KC_LGUI,    MO(1),       B_MOUSE,             KC_NO,    KC_SPC,     MO(2)                        
  ),
  // Macro layer
	[1] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_1,       KC_2,       KC_3,       QK_CLEAR_EEPROM,       M_SWITCH_MOUSE,               KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_BSPC,
    KC_ESC,    KC_4,       KC_5,       KC_6,       M_ALFRED,    M_HMRW,              KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_NO,
    KC_LSFT,   KC_7,       KC_8,       KC_9,       M_SCRSHT,    KC_NO,             KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_LCTL,
                                       KC_0,       MO(1),       B_MOUSE,             KC_NO,    KC_SPC,      MO(2)                          
  ),
  // Symbolic/numeric layer
  [2] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_EXLM,    KC_AT,      KC_LBRC,    KC_RBRC,       KC_PIPE,             KC_UP,    KC_7,     KC_8,    KC_9,  KC_ASTR,  KC_RABK,
    KC_ESC,    KC_HASH,    KC_DLR,     KC_LPRN,    KC_RPRN,       KC_GRV,              KC_DOWN,  KC_4,     KC_5,    KC_6,  KC_PLUS,  KC_LABK,
    KC_LSFT,   KC_PERC,    KC_CIRC,    KC_LCBR,    KC_RCBR,       KC_TILD,             KC_AMPR,  KC_1,     KC_2,    KC_3,  KC_SLSH,  KC_EQL,
                                       KC_LGUI,    MO(1),         B_MOUSE,             KC_NO,    KC_SPC,   KC_0                        
  ),
};

// Modify these alues to adjust the scrolling speed
#define SCROLL_DIVISOR_H 10
#define SCROLL_DIVISOR_V 10

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Modify these to adjust non-linear mouse scaling
#define MAX_SCALE 32
#define MIN_SCALE 0.5
#define GROWTH_FACTOR 1
#define MOMENTUM 0.1
#define RESET_MOMENTUM 1 // After 1 second of inactivity, reset the momentum

// Variable to store an exponential moving average scaling factor to denoise the non-linear scaling
float accumulated_factor = MIN_SCALE;
int last_update_timestamp = 0;
report_mouse_t last_left_report;
report_mouse_t last_right_report;



// Arrow keys slight slowing
#define ARROW_STEP 20
int accumulated_arrow_x = 0;
int accumulated_arrow_y = 0;

float average_arrow_x = 0;
float average_arrow_y = 0;

#define ARROW_MOMENTUM 0.01

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Get time elapsed since last update
    int current_timestamp = time(NULL);
    int time_elapsed = current_timestamp - last_update_timestamp;
    last_update_timestamp = current_timestamp;
    if (!has_mouse_report_changed(&left_report, &last_left_report) && !has_mouse_report_changed(&right_report, &last_right_report) && time_elapsed > RESET_MOMENTUM) {
        // If no mouse movement has been detected, reset the momentum
        accumulated_factor = MIN_SCALE;
    }

    // If the time elapsed is over 
    report_mouse_t main_report = right_report;
    report_mouse_t sub_report = left_report;
    if (mouse_switch) {
        main_report = left_report;
        sub_report = right_report;
    }
    
    // Layer not 2: sub trackball scroll, main trackball mouse
    if (!layer_state_is(2)) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)sub_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)sub_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        sub_report.h = -(int16_t)scroll_accumulated_h;
        sub_report.v = (int16_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int16_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int16_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        sub_report.x = 0;
        sub_report.y = 0;

        // still treat right trackball behavior as normal.
        // compute the size of the last mouse movement
        float mouse_length = sqrt(main_report.x*main_report.x + main_report.y*main_report.y);

        // compute an instantaneous scaling factor and update exponential moving average
        float factor =  GROWTH_FACTOR*mouse_length+ MIN_SCALE;
        accumulated_factor = accumulated_factor*(1-MOMENTUM) + factor*MOMENTUM;

        if (accumulated_factor > MAX_SCALE) {
            // clamp the scaling factor to avoid overflowing main_report
            main_report.x *= MAX_SCALE;
            main_report.y *= MAX_SCALE;
        }
        else {
            // scale up the mouse movement by the average factor
            main_report.x = (int16_t)(main_report.x * accumulated_factor);
            main_report.y = (int16_t)(main_report.y * accumulated_factor);
        }
    }

    // Layer 2: sub trackball arrow keys, main trackball mouse
    if (layer_state_is(2)) {
        // move one space per click here, biasing towards vertical
        // if you are moving in text horizontally and click an accidental
        // vertical, you can just click back.  If you are moving vertically
        // and send an accidental horizontal, you can't just click back
        // if you are in a line shorter than where you started.  Thus,
        // you should strongly prefer vertical movement to bias against
        // accidental sideways clicks.  Almost all text scrolling is
        // orthogonal, so this helps suppress diagonal motion.  Think of it
        // as if you are in a box, and you move when you hit an edge, 
        // resetting to the center each time.  

        // This version additionally keeps a running average and only allows
        // motion in the direction of the recent average 

        // update the accumulated arrow momentum
        average_arrow_x = average_arrow_x*ARROW_MOMENTUM + (float) sub_report.x*(1-ARROW_MOMENTUM);
        average_arrow_y = average_arrow_y*ARROW_MOMENTUM + (float) sub_report.y*(1-ARROW_MOMENTUM);

        // kill accumulated clicks orthogonal to average direction           
        if (fabs(average_arrow_x) > fabs(average_arrow_y)){
            accumulated_arrow_x += sub_report.x;
            accumulated_arrow_y = 0;
        }
        if (fabs(average_arrow_y) > fabs(average_arrow_x)){
            accumulated_arrow_x = 0;
            accumulated_arrow_y += sub_report.y;
        }
    
        // process queued clicks
        if (accumulated_arrow_x <= -ARROW_STEP){
            tap_code(KC_LEFT);
            accumulated_arrow_x += ARROW_STEP;
        }
        if (accumulated_arrow_x >= ARROW_STEP) {
            tap_code(KC_RIGHT);
            accumulated_arrow_x -= ARROW_STEP;
        }
        if (accumulated_arrow_y <= -ARROW_STEP){
            tap_code(KC_UP);
            accumulated_arrow_y += ARROW_STEP;
        }
        if (accumulated_arrow_y >= ARROW_STEP) {
            tap_code(KC_DOWN);
            accumulated_arrow_y -= ARROW_STEP;
        }
        
        // get a null report for left trackball
        sub_report.x = 0;
        sub_report.y = 0;

        // still treat right trackball behavior as normal.
        // compute the size of the last mouse movement
        float mouse_length = sqrt(main_report.x*main_report.x + main_report.y*main_report.y);

        // compute an instantaneous scaling factor and update exponential moving average
        float factor =  GROWTH_FACTOR*mouse_length+ MIN_SCALE;
        accumulated_factor = accumulated_factor*(1-MOMENTUM) + factor*MOMENTUM;

        if (accumulated_factor > MAX_SCALE) {
            // clamp the scaling factor to avoid overflowing main_report
            main_report.x *= MAX_SCALE;
            main_report.y *= MAX_SCALE;
        }
        else {
            // scale up the mouse movement by the average factor
            main_report.x = (int16_t)(main_report.x * accumulated_factor);
            main_report.y = (int16_t)(main_report.y * accumulated_factor);
        }
    }

    // Left is sub, right is main
    if (mouse_switch) {
        return pointing_device_combine_reports(sub_report, main_report);
        // Save reports
        last_left_report = sub_report;
        last_right_report = main_report;
    // Right is sub, left is main
    } else {
        return pointing_device_combine_reports(main_report, sub_report);
        // Save reports
        last_left_report = main_report;
        last_right_report = sub_report;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        pimoroni_trackball_set_rgbw(0,0,0,255);
        break;
    case 1:
        pimoroni_trackball_set_rgbw(192,0,64,0);
        break;
    case 2:
        pimoroni_trackball_set_rgbw(0,192,128,0);
        break;
    case 3:
        pimoroni_trackball_set_rgbw(153,113,0,0);
        break;
    }
  return state;
}

void keyboard_post_init_user(void) {
    // default trackball to white
	  pimoroni_trackball_set_rgbw(0,0,0,255);
    // pointing_device_set_cpi_on_side(true, 1000); //Set cpi on left side to a low value for slower scrolling.
    // pointing_device_set_cpi_on_side(false, 1); //Set cpi on right side to a reasonable value for mousing.
}

void suspend_power_down_user(void) {
	  pimoroni_trackball_set_rgbw(0,0,0,0);
}

void suspend_wakeup_init_user(void) {
    pimoroni_trackball_set_rgbw(0,0,0,255);
}