/* Copyright 2019 imchipwood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define _BASE 0
#define _SUB  1
#define _GIT  1
#define _JUNOS  2

enum custom_keycodes {
  GIT_PULL = SAFE_RANGE,
  GIT_PUSH, GIT_COMMIT, GIT_STATUS, GIT_DIFF,
  COMMIT_CHECK,
  SHOW_COMPARE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
        BASE LAYER
        replaced KC_SLASH with RESET
  */
  [_BASE] = LAYOUT(
                   TO(_GIT),  RESET, S(KC_8),  KC_NO, 
                   KC_7,      KC_8,     KC_9,     S(KC_EQUAL), 
                   KC_4,      KC_5,     KC_6,     KC_NO, 
                   KC_1,      KC_2,     KC_3,     KC_ENTER, 
                   KC_NO,     KC_0,     KC_DOT,   KC_NO,
                   KC_NO,     KC_NO,    KC_MINUS, KC_NO
  ),
  /*
        GIT LAYER
  */
  [_GIT] = LAYOUT(
                 TO(_JUNOS),   RESET,       KC_NO,      KC_NO, 
                 KC_NO,     KC_NO,     KC_NO,      KC_KP_PLUS, 
                 GIT_STATUS,  GIT_DIFF,     KC_NO,      KC_KP_MINUS, 
                 GIT_PULL,    GIT_PUSH,    GIT_COMMIT,      KC_ENTER,
                 KC_NO,     KC_NO,     KC_NO,      KC_NO,
                 KC_NO,     KC_NO,     KC_NO,      KC_NO
  ),
  /*
        JUNOS LAYER
  */
  [_JUNOS] = LAYOUT(
                 TO(_BASE),   RESET,       KC_NO,      KC_NO, 
                 KC_NO,     KC_NO,     KC_NO,      KC_NO, 
                 KC_NO,     KC_NO,     KC_NO,      KC_NO, 
                 COMMIT_CHECK,     SHOW_COMPARE,     KC_NO,      KC_ENTER,
                 KC_NO,     KC_NO,     KC_NO,      KC_NO,
                 KC_NO,     KC_NO,     KC_NO,      KC_NO
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GIT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull\n");
            }
            return false;
            break;
        case GIT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push\n");
            }
            return false;
            break;
        case GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m \"");
            }
            return false;
            break;
        case GIT_DIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff\n");
            }
            return false;
            break;
        case GIT_STATUS:
            if (record->event.pressed) {
                SEND_STRING("git status\n");
            }
            return false;
            break;
        case COMMIT_CHECK:
            if (record->event.pressed) {
                SEND_STRING("commit check");
            }
            return false;
            break;
        case SHOW_COMPARE:
            if (record->event.pressed) {
                SEND_STRING("show | compare\n");
            }
            return false;
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Default behavior:
   *    main layer:
   *       CW: move mouse right
   *      CCW: move mouse left
   *    other layers:
   *       CW: = (equals/plus - increase slider in Adobe products)
   *      CCW: - (minus/underscore - decrease slider in adobe products)
   */
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        // main layer - move mouse right (CW) and left (CCW)
        if (clockwise) {
          tap_code(KC_MS_R);
        } else {
          tap_code(KC_MS_L);
        }
        break;

      default:
        // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
        if (clockwise) {
          tap_code(KC_EQL);
        } else {
          tap_code(KC_MINS);
        }
        break;
    }
  }
}
