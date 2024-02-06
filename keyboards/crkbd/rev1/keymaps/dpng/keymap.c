#include "action.h"
#include "math.h"
#include "dpng.h"
#include QMK_KEYBOARD_H

#define BW_TAP_TIME 200  //configure max tap time, 200ms here

enum custom_keycodes {
  BW_BTN1_BTN2 = SAFE_RANGE, // Combined click (KC_BTN1) and right click (KC_BTN2) (never got this one to work)
  BW_TAB_L3, // Combined tab and activate layer 3 when held
  BW_ENTER_CTL, // Combined enter and ctrl
  BW_SPC_ALT, // Combined space and alt
  M_ALFRED, // Opens alfred in arc mode
  M_HMRW, // Opens homerow
  M_SCRSHT, // Activates screenshot mode on mac
  M_ARROW, // Types pythonic arrow
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t tab_l3_timer;
  static uint16_t enter_ctl_timer;
  static uint16_t spc_alt_timer;
  static uint16_t btn1_btn2_timer;
  switch (keycode) {

    // combined click (KC_BTN1) and right click (KC_BTN2)
    case BW_BTN1_BTN2:
      if (record->event.pressed) {
        btn1_btn2_timer = timer_read();
        register_code(KC_BTN2);
      } else {
        unregister_code(KC_BTN2);
        if (timer_elapsed(btn1_btn2_timer) < BW_TAP_TIME)
          tap_code(KC_BTN1);
      }
      return false;
    // Combined tab and l3 key
    case BW_TAB_L3:
      if (record->event.pressed) {
        tab_l3_timer = timer_read();
        layer_on(3); 
      } else {
        layer_off(3);
        if (timer_elapsed(tab_l3_timer) < BW_TAP_TIME)
          tap_code(KC_TAB);
      }
      return false;
    // combined enter and control key
    case BW_ENTER_CTL:
      if (record->event.pressed) {
        enter_ctl_timer = timer_read();
        register_code(KC_LCTL); 
      } else {
        unregister_code(KC_LCTL); 
        if (timer_elapsed(enter_ctl_timer) < BW_TAP_TIME)
          tap_code(KC_ENT);
      }
      return false;
    // combined space and alt key
    case BW_SPC_ALT:
      if (record->event.pressed) {
        spc_alt_timer = timer_read();
        register_code(KC_RALT); 
      } else {
        unregister_code(KC_RALT); 
        if (timer_elapsed(spc_alt_timer) < BW_TAP_TIME)
          tap_code(KC_SPC);
      }
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
    // Types pythonic arrow
    case M_ARROW:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
  }
  return true;
}

// Organization is 6 keys per row, thumb cluster has 3 keys on left and 2 keys on right (a gap is left for the trackball on the right thumb).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Regular keys
  [0] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_Q,       KC_W,       KC_E,       KC_R,        KC_T,                KC_Y,     KC_U,       KC_I,       KC_O,      KC_P,     KC_BSPC,
    KC_ESC,    KC_A,       KC_S,       KC_D,       KC_F,        KC_G,                KC_H,     KC_J,       KC_K,       KC_L,      KC_SCLN,  KC_QUOT,
    KC_LSFT,   KC_Z,       KC_X,       KC_C,       KC_V,        KC_B,                KC_N,     KC_M,       KC_COMM,    KC_DOT,    KC_SLSH,  KC_ENTER,
                                       KC_LGUI,    MO(2),       KC_BTN1,             KC_NO,    KC_SPC,     MO(1)                        
  ),
  // General use macros, numbers
	[1] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_1,       KC_2,       KC_3,       KC_NO,       KC_NO,               KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_BSPC,
    KC_ESC,    KC_4,       KC_5,       KC_6,       M_ALFRED,    M_HMRW,              KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_NO,
    KC_LSFT,   KC_7,       KC_8,       KC_9,       M_SCRSHT,    M_ARROW,             KC_NO,    KC_NO,       KC_NO,      KC_NO,    KC_NO,    KC_LCTL,
                                       KC_0,       MO(2),       KC_BTN2,             KC_NO,    KC_SPC,      MO(1)                          
  ),
  // Programming characters and vim macros
  [2] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_EXLM,    KC_AT,      KC_HASH,    KC_NO,       KC_NO,               KC_EQL,   KC_LCBR,     KC_RCBR,    KC_PIPE,  KC_P,     KC_BSPC,
    KC_ESC,    KC_HASH,    KC_PERC,    KC_CIRC,    M_ALFRED,    M_HMRW,              KC_MINS,  KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_SCLN,  KC_DQUO,
    KC_LSFT,   KC_AMPR,    KC_ASTR,    KC_NO,      KC_NO,       KC_NO,               KC_UNDS,  KC_LABK,     KC_RABK,    KC_GRAVE, KC_TILD,  KC_ENTER,
                                       KC_LGUI,    MO(2),       KC_BTN2,             KC_NO,    KC_SPC,      MO(1)                        
  ),
  // ? Haven't figured out what to put here yet. Probably system stuff.
  [2] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_EXLM,    KC_AT,      KC_HASH,    KC_NO,       KC_NO,               KC_EQL,   KC_LCBR,     KC_RCBR,    KC_PIPE,  KC_P,     KC_BSPC,
    KC_ESC,    KC_HASH,    KC_PERC,    KC_CIRC,    KC_NO,       KC_NO,               KC_MINS,  KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_SCLN,  KC_DQUO,
    KC_LSFT,   KC_AMPR,    KC_ASTR,    KC_NO,      KC_NO,       KC_NO,               KC_UNDS,  KC_LABK,     KC_RABK,    KC_GRAVE, KC_TILD,  KC_ENTER,
                                       KC_LGUI,    MO(2),       KC_BTN2,             KC_NO,    KC_SPC,      MO(1)                        
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
#define MIN_SCALE 0.0001
#define GROWTH_FACTOR 16
#define MOMENTUM 0.0005

// Variable to store an exponential moving average scaling factor to denoise the non-linear scaling
float accumulated_factor = MIN_SCALE;

// Arrow keys slight slowing
#define ARROW_STEP 4
int accumulated_arrow_x = 0;
int accumulated_arrow_y = 0;

float average_arrow_x = 0;
float average_arrow_y = 0;

#define ARROW_MOMENTUM 0.99

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {

    // Layer not 2: left trackball scroll, right trackball mouse
    if (!layer_state_is(2)) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        left_report.h = -(int16_t)scroll_accumulated_h;
        left_report.v = (int16_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int16_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int16_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        left_report.x = 0;
        left_report.y = 0;

        // still treat right trackball behavior as normal.
        // compute the size of the last mouse movement
        float mouse_length = sqrt(right_report.x*right_report.x + right_report.y*right_report.y);

        // compute an instantaneous scaling factor and update exponential moving average
        float factor =  GROWTH_FACTOR*mouse_length+ MIN_SCALE;
        accumulated_factor = accumulated_factor*(1-MOMENTUM) + factor*MOMENTUM;

        if (accumulated_factor > MAX_SCALE) {
            // clamp the scaling factor to avoid overflowing right_report
            right_report.x *= MAX_SCALE;
            right_report.y *= MAX_SCALE;
        }
        else {
            // scale up the mouse movement by the average factor
            right_report.x = (int16_t)(right_report.x * accumulated_factor);
            right_report.y = (int16_t)(right_report.y * accumulated_factor);
        }
    }

    // Layer 2: left trackball arrow keys, right trackball mouse
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
        average_arrow_x = average_arrow_x*ARROW_MOMENTUM + (float) left_report.x*(1-ARROW_MOMENTUM);
        average_arrow_y = average_arrow_y*ARROW_MOMENTUM + (float) left_report.y*(1-ARROW_MOMENTUM);

        // kill accumulated clicks orthogonal to average direction           
        if (fabs(average_arrow_x) > fabs(average_arrow_y)){
            accumulated_arrow_x += left_report.x;
            accumulated_arrow_y = 0;
        }
        if (fabs(average_arrow_y) > fabs(average_arrow_x)){
            accumulated_arrow_x = 0;
            accumulated_arrow_y += left_report.y;
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
        left_report.x = 0;
        left_report.y = 0;

        // still treat right trackball behavior as normal.
        // compute the size of the last mouse movement
        float mouse_length = sqrt(right_report.x*right_report.x + right_report.y*right_report.y);

        // compute an instantaneous scaling factor and update exponential moving average
        float factor =  GROWTH_FACTOR*mouse_length+ MIN_SCALE;
        accumulated_factor = accumulated_factor*(1-MOMENTUM) + factor*MOMENTUM;

        if (accumulated_factor > MAX_SCALE) {
            // clamp the scaling factor to avoid overflowing right_report
            right_report.x *= MAX_SCALE;
            right_report.y *= MAX_SCALE;
        }
        else {
            // scale up the mouse movement by the average factor
            right_report.x = (int16_t)(right_report.x * accumulated_factor);
            right_report.y = (int16_t)(right_report.y * accumulated_factor);
        }
    }

    return pointing_device_combine_reports(left_report, right_report);
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