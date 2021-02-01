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

#define _BASE   0
#define _MODE	1
#define _ZOOM	2
#define _WSJT	3


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
	_BASE layer
		mute     / step up / step down / alt-tab
		SMUTEALL / STEPINC / STEPDEC   / alt-tab
		S+F9     / S+F16   / S+F17     / A+TAB
  */
  [_BASE] = LAYOUT(
    	TO(_MODE), LSFT(KC_F9), LSFT(KC_F16), LSFT(KC_F17), LALT(KC_TAB)
  ),



  /*
	_MODE layer
		mute     / mode up   / mode down / alt-tab
		SMUTEALL / SMODENEXT / SMODEPREV / alt-tab
		S+F9     / S+F14   / S+F15       / A+TAB
  */
  [_MODE] = LAYOUT(
    	TO(_ZOOM), LSFT(KC_F9), LSFT(KC_F14), LSFT(KC_F15), LALT(KC_TAB)
  ),



  /*
	_ZOOM layer	
		mute     / zoom up   / zoom down / pan center
		SMUTEALL / PANBW_UP  / PANBW_DOWN / PANCENTER
		S+F9     / S+F10     / S+F11       / S+F13
  */
  [_ZOOM] = LAYOUT(
    	TO(_WSJT), LSFT(KC_F9), LSFT(KC_F10), LSFT(KC_F11), LSFT(KC_F13)
  ),



  /*
	_WSJT layer	
		mute     / enable tx / erase / halt tx
		S+F9     / ALT+N     / ALT+E / ALT+H
  */
  [_WSJT] = LAYOUT(
    	TO(_BASE), LSFT(KC_F9), LALT(KC_N), LALT(KC_E), LALT(KC_H)
  ),


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void keyboard_post_init_user(void) {

}

void matrix_init_user(void) {

}


// OLED Driver Logic
#ifdef OLED_DRIVER_ENABLE


void oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Mute\nStep UP\nStep Down\nALT-TAB\n"), false);
            break;
        case _MODE:
            oled_write_P(PSTR("Mute\nMode UP\nMode Down\nALT-TAB\n"), false);
            break;
        case _ZOOM:
            oled_write_P(PSTR("Mute\nPan out\nPan in\nPan center\n"), false);
            break;
        case _WSJT:
            oled_write_P(PSTR("Mute\nEnable TX\nErase\nHalt TX\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    // led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

#endif

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}


void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Cusotom behavior:
   *    main layer:
   *       CW: volume up
   *      CCW: volume down
   *    sub layer:
   *       CW: next media track
   *      CCW: prev media track
   *    debug layer:
   *       CW: brightness up
   *      CCW: brightness down
   */
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        if (clockwise) {
          tap_code(KC_MS_WH_UP);
        } else {
          tap_code(KC_MS_WH_DOWN);
        }
        break;

      //in WSJT -- turn the knob off
      case _WSJT:
        if (clockwise) {
          tap_code(KC_NO);
        } else {
          tap_code(KC_NO);
        }
        break;

      default:
        // any other layer (shouldn't exist..) - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_MS_WH_UP);
        } else {
          tap_code(KC_MS_WH_DOWN);
        }
        break;   
    }
  }
}
