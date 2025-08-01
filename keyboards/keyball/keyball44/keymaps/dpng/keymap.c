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
#define E_ALFD LT(0, KC_E)
#define R_HMRW LT(0, KC_R)
#define W_SCRSHT LT(0, KC_W)
// custom bettertouchtool script which is used to open ghostty upon typing cmd option y
#define Y_GHOSTTY LT(0, KC_Y)
#define X_HMRW_SCROLL LT(0, KC_X)
#define C_HMRW_SEARCH LT(0, KC_C)
#define ESC_CAPSLOCK LT(0, KC_ESC)
#define Z_UNDO LT(0, KC_Z)
// TODO: viable cheatsheet
#define Q_CHEAT LT(0, KC_Q)
#define SLSH LT(0, KC_SLSH)
#define SPC_CTRL LT(0, KC_SPC)

enum custom_keycodes {
  M_SCRREC = SAFE_RANGE, // Starts a screen recording
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
    case SLSH:
      if (!record->tap.count && record->event.pressed) {
        tap_code16(KC_SLSH);
      } else if (record->event.pressed) {
        tap_code16(KC_BSLS);
      }
      return false;
    case Q_CHEAT:
      if (!record->tap.count && record->event.pressed) {
        // Send a cheatsheet as typed text
        SEND_STRING("=== KEYMAP CHEATSHEET ===\n"
                   "HOME ROW MODS:\n"
                   "A=Cmd S=Alt D=Ctrl F=Shift \n\n"
                   "SPECIAL HOLDS:\n"
                   "Q=Cheatsheet W=Screenshot E=Alfred R=Homerow X=Scroll C=Search\n"
                   "G=Numbers H=Symbols Enter=Navigation  \n\n"
                   "NUMBERS (Hold G): Q=1 W=2 E=3 R=4 T=5 Y=6 U=7 I=8 O=9 P=0\n\n"
                   "SYMBOLS (Hold H):\n"
                   "Top: Q=! W=@ E=# R=$ T=% Y=^ U=& I=* O=( P=)\n"
                   "Home: A=[ S=] D={ F=} G=\\ J=_ I=+ K=- L==\n\n"
                   "SHORTCUTS:\n"
                   "Z=Undo(Cmd+Z)\n"
                   "Common: Cmd+C Cmd+V Cmd+S Cmd+W via home row mods\n");
      }
      return true;
    // takes screenshot
    case W_SCRSHT:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift 4
        SEND_STRING(SS_LGUI(SS_LSFT("4")));
      }
      return true;
    // focuses/defocuses ghostty
    case Y_GHOSTTY:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd option y
        SEND_STRING(SS_LGUI(SS_LALT("y")));
      }
      return true;

    case E_ALFD:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd space
        SEND_STRING(SS_LGUI(" "));
      }
      return true;
    // activates homerow
    case R_HMRW:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift r
        SEND_STRING(SS_LGUI(SS_LSFT("r")));
      }
      return true;  
    case X_HMRW_SCROLL:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is ctrl cmd shift m
        SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT("m"))));
      }
      return true;  
    case C_HMRW_SEARCH:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is ctrl cmd shift f
        SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT("f"))));
      }
      return true;  
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
    case M_SCRREC:
      if (!record->tap.count && record->event.pressed) {
        // Sequence is cmd shift 5
        SEND_STRING(SS_LGUI(SS_LSFT("5")));
      }
      return true;
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
    KC_TAB   ,        KC_Q     , W_SCRSHT  ,        E_ALFD            , R_HMRW         ,  KC_T    , Y_GHOSTTY, KC_U        , KC_I           , KC_O     , KC_P     , KC_DEL   ,
    KC_ESC   , LGUI_T(KC_A), LALT_T(KC_S),  LCTL_T(KC_D), LSFT_T(KC_F),  LT(1, KC_G)   , LT(2, KC_H)   , KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT  ,
    KC_LGUI  ,        Z_UNDO   , X_HMRW_SCROLL     ,        KC_C          , KC_V       ,  KC_B    , KC_N          , KC_M        , KC_COMM        , KC_DOT   , KC_SLSH  , KC_LCTL ,
                      KC_LALT  , KC_LCTL  ,        KC_RSFT         , KC_SPC       , KC_BTN1 , KC_BSPC,        LT(3, KC_ENT),_______        , _______ , KC_PSCR
  ),
  // numbers layer (hold G)
  [1] = LAYOUT_universal(
    _______,      KC_1,         KC_2,       KC_3,       KC_4,          KC_5,                KC_6,           KC_7,          KC_8,    KC_9,    KC_0,     _______,
    _______,      _______,      _______,    _______,    _______,       _______,             _______,        _______,       _______,  _______,  _______,  _______,
    _______,      _______,      _______,    _______,    _______,       _______,             _______,        _______,       _______,  _______,  _______,  _______,
                  _______,      _______,    _______,    _______,           _______,             _______,        KC_SPC,  _______, _______, _______ 
  ),
  // symbols layer (hold H)  
  [2] = LAYOUT_universal(
    _______,      KC_EXLM,      KC_AT,      KC_HASH,    KC_DLR,        KC_PERC,             KC_CIRC,        KC_AMPR,       KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
    _______,      KC_LBRC,      KC_RBRC,    KC_LCBR,    KC_RCBR,       KC_PIPE,             _______,        KC_UNDS,       KC_PLUS,  KC_MINS,  KC_EQL,   _______,
    _______,      KC_GRV,       KC_TILD,    _______,    _______,       _______,             _______,        KC_BSLS,       _______,  _______,  _______,  _______,
                  _______,      _______,    _______,    _______,           _______,             _______,        KC_SPC,  _______, _______, _______ 
  ),
  // navigation layer
  [3] = LAYOUT_universal(
    KC_TAB,    KC_NO,       KC_NO,       KC_UP,                 KC_NO,           KC_NO,                KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
    KC_NO,     KC_NO,       KC_RIGHT,    KC_DOWN,               KC_LEFT,         KC_NO,               KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
    KC_NO,     KC_NO,       KC_NO,       KC_NO,     KC_NO,      KC_NO	,     KC_NO,          KC_NO,       KC_NO,       KC_NO,      KC_NO,     KC_NO,
               KC_LGUI,     KC_LGUI,     KC_NO,                 KC_LEFT_ALT,         KC_BTN1,               KC_BSPC,        KC_NO,     _______    , _______  ,  KC_PSCR  
  ),
};
// clang-format on


layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
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