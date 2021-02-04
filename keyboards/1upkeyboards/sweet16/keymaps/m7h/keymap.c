/* a crazy use of hardware */
/* make 1upkeyboards/sweet16/v1:m7h:avrdude */


#include QMK_KEYBOARD_H

#define _BASE 0
#define _SECOND 1

enum custom_keycodes {
  FFS = SAFE_RANGE,
  COMMIT_CHECK,
  SHOW_COMPARE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   KC_ASTR,
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        KC_0, KC_ENT, KC_DOT, MO(_SECOND)
    ),
    [_SECOND] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   KC_ASTR,
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        FFS, COMMIT_CHECK, SHOW_COMPARE, KC_EQL
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FFS:
            if (record->event.pressed) {
                SEND_STRING("oh ffs");
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

#ifdef ENCODER_ENABLE
#include "encoder.h"
void encoder_update_user(int8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
}
#endif
