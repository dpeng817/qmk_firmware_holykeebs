/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "print.h"

#define BTN_MOUSE LT(0, KC_BTN1)
#define F_HMRW LT(0, KC_F)
#define D_ALFD LT(0, KC_D)
#define C_COPY LT(0, KC_C)
#define V_PSTE LT(0, KC_V)
#define W_CLOSE LT(0, KC_W)
#define ESC_CAPSLOCK LT(0, KC_ESC)
#define Z_UNDO LT(0, KC_Z)
#define S_SAVE LT(0, KC_S)
#define SLSH LT(0, KC_SLSH)
#define PERC_REDO LT(0, KC_PERC)
#define LCBR_URL LT(0, KC_LCBR)
#define SPC_CTRL LT(0, KC_SPC)

enum custom_keycodes {
  M_SCRSHT = SAFE_RANGE, // Takes a screenshot
  M_SCRREC, // Starts a screen recording
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BTN_MOUSE:
      if(record->tap.count && record->event.pressed) {
        tap_code16(KC_BTN1);
      } 
      else if (record->event.pressed) {
        tap_code16(KC_BTN2);
      }
      return false;
    // opens alfred in arc mode
    case D_ALFD:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd space (delay 50) space
        SEND_STRING(SS_LGUI(" ") SS_DELAY(50) SS_TAP(X_SPC));
      }
      return true;
    // activates homerow
    case F_HMRW:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift s
        SEND_STRING(SS_LGUI(SS_LSFT("s")));
      }
      return true;
    case SLSH:
      if (!record->tap.count && record->event.pressed) {
        tap_code16(KC_SLSH);
      } else if (record->event.pressed) {
        tap_code16(KC_BSLS);
      }
      return false;
    case C_COPY:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd c
        SEND_STRING(SS_LGUI("c"));
      } else if (record->event.pressed) {
        tap_code16(KC_C);
      }
      return false;
    case V_PSTE:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd v
        SEND_STRING(SS_LGUI("v"));
      } else if (record->event.pressed) {
        tap_code16(KC_V);
      }
      return false;
    case W_CLOSE:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd w
        SEND_STRING(SS_LGUI("w"));
      } else if (record->event.pressed) {
        tap_code16(KC_W);
      }
      return false;  
    case ESC_CAPSLOCK:
      if (!record->tap.count && record->event.pressed) {
        // Press caps lock
        tap_code16(KC_CAPS);
      } else if (record->event.pressed) {
        tap_code16(KC_ESC);
      }
      return false;
    case Z_UNDO:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd z
        SEND_STRING(SS_LGUI("z"));
      } else if (record->event.pressed) {
        tap_code16(KC_Z);
      }
      return false;
    case PERC_REDO:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shft z
        SEND_STRING(SS_LGUI(SS_LSFT("z")));
      } else if (record->event.pressed) {
        tap_code16(KC_PERC);
      }
      return false;
    case LCBR_URL:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift c
        SEND_STRING(SS_LGUI(SS_LSFT("c")));
      } else if (record->event.pressed) {
        tap_code16(KC_LCBR);
      }
      return false;
    case M_SCRSHT:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift 4
        SEND_STRING(SS_LGUI(SS_LSFT("4")));
      }
      return true;
    case M_SCRREC:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift 5
        SEND_STRING(SS_LGUI(SS_LSFT("5")));
      }
      return true;
    case S_SAVE:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd s
        SEND_STRING(SS_LGUI("s"));
      } else if (record->event.pressed) {
        tap_code16(KC_S);
      }
      return false;
    case SPC_CTRL:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd s
        SEND_STRING(SS_LCTL(" "));
      } else if (record->event.pressed) {
        tap_code16(KC_SPC);
      }
      return false;
  }
  return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB   ,        KC_Q     , W_CLOSE  ,        KC_E            , KC_R         ,  KC_T           ,                                        KC_Y          , KC_U        , KC_I           , KC_O     , KC_P     , KC_DEL   ,
    KC_ESC   , KC_A     , S_SAVE   ,        D_ALFD          , F_HMRW       ,  KC_G           ,                                               KC_H          , LT(2, KC_J) , KC_K           , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  ,        Z_UNDO   , KC_X     ,        C_COPY          , V_PSTE       ,  KC_B           ,                                        KC_N          , KC_M        , KC_COMM        , KC_DOT   , KC_SLSH  , KC_ENTER ,
                      KC_LALT  , KC_LCTL  ,        KC_LGUI         , KC_LCTL       , KC_BTN1        ,                                        KC_BSPC,        LT(1, KC_SPC),_______        , _______ , KC_PSCR
  ),
  // programming symbols
  [1] = LAYOUT_universal(
    KC_TAB,       KC_EXLM,      KC_AT,      KC_LBRC,    KC_RBRC,       KC_PIPE,             KC_AMPR,        KC_7,          KC_8,    KC_9,    KC_ASTR,  SLSH,
    KC_NO,        KC_HASH,      KC_DLR,     KC_LPRN,    KC_RPRN,       KC_GRV,              KC_UNDS,        KC_4,          KC_5,    KC_6,    KC_PLUS,  KC_EQL,
    KC_NO,        PERC_REDO,    KC_CIRC,    LCBR_URL,   KC_RCBR,       KC_TILD,             KC_MINS,        KC_1,          KC_2,    KC_3,    KC_0,     KC_ENTER,
                  KC_LGUI,      KC_LGUI,    KC_LGUI,    KC_LEFT_ALT,       KC_BTN1,             KC_BSPC,        KC_NO,  _______, _______, KC_PSCR 
  ),
  // navigation
  [2] = LAYOUT_universal(
    KC_TAB,    KC_NO,       KC_NO,       KC_UP,                 KC_NO,           KC_NO,                KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
    KC_NO,     KC_NO,       KC_RIGHT,    KC_DOWN,               KC_LEFT,         KC_NO,               KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
    KC_NO,     KC_NO,       KC_NO,       KC_NO,     KC_NO,      KC_NO	,     KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
               KC_LGUI,     KC_LGUI,     KC_NO,                 KC_LEFT_ALT,         KC_BTN1,               KC_BSPC,        KC_NO,     _______    , _______  ,  KC_PSCR  
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 2);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    //keyball_oled_render_keyinfo();
    //keyball_oled_render_ballinfo();
    //keyball_oled_render_layerinfo();
}
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
  return pointing_device_combine_reports(left_report, right_report);
}