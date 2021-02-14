/* a crazy use of hardware */
/* make 1upkeyboards/sweet16/v1:m7h:avrdude */


#include QMK_KEYBOARD_H

#define _BASE 0
#define _SECOND 1

#define PLEX_LED_0	D7
#define PLEX_LED_1	E6
#define PLEX_LED_2	B4
#define PLEX_LED_3	B5

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



// LED initialization
void matrix_init_kb(void) {
	setPinOutput(PLEX_LED_0);
	setPinOutput(PLEX_LED_1);
	setPinOutput(PLEX_LED_2);
	setPinOutput(PLEX_LED_3);

	//second LED
	//wait_ms(100);
	//writePinHigh(PLEX_LED_0);
	//wait_ms(500);
	//writePinLow(PLEX_LED_0);

	//first LED
	//wait_ms(200);
	//writePinHigh(PLEX_LED_2);
	//wait_ms(500);
	//writePinLow(PLEX_LED_2);

	//cycle through LEDs on init
	for (int a = 0; a < 4; a++) {
		writePinHigh(PLEX_LED_2);
		wait_ms(50);
		writePinHigh(PLEX_LED_0);
		wait_ms(50);
		writePinLow(PLEX_LED_2);
		wait_ms(50);
		writePinLow(PLEX_LED_0);
		wait_ms(100);
	}
	matrix_init_user();
}



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
