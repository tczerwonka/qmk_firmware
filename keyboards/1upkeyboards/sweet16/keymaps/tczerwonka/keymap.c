/* a crazy use of hardware */
/* make 1upkeyboards/sweet16/v1:m7h:avrdude */


#include QMK_KEYBOARD_H

#define _BASE 	0
#define _OTHER 	1
#define _V6 	2

#define PLEX_LED_0	D7
#define PLEX_LED_1	E6
#define PLEX_LED_2	B4
#define PLEX_LED_3	B5

enum custom_keycodes {
  FFS = SAFE_RANGE,
  COMMIT_CHECK,
  SHOW_COMPARE,
  GIT_DIFF,
  GIT_ADD,
  GIT_PUSH,
  GIT_COMMIT,
  COLON_COLON,
  ONETWENTYSEVEN,
  OHFFS
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   TO(_OTHER),
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_PLUS,
        KC_0, KC_DOT, KC_MINS, KC_ENT
    ),
    [_OTHER] = LAYOUT_ortho_4x4(
        FFS, 		OHFFS,   	KC_NO,   	TO(_V6),
        A(KC_TAB), 	KC_VOLD,   	KC_VOLU,   	KC_MUTE,
        GIT_DIFF, 	GIT_ADD,   	GIT_COMMIT,   	GIT_PUSH,
        KC_SPACE, 	COMMIT_CHECK, 	SHOW_COMPARE, 	KC_ENT
    ),
    [_V6] = LAYOUT_ortho_4x4(
        KC_7, 	KC_8,   	KC_9,		TO(_BASE),
        KC_4, 	KC_5,   	KC_6,		ONETWENTYSEVEN,
        KC_1, 	KC_2,   	KC_3,		KC_SLSH,
        KC_0, 	S(KC_SCOLON), 	COLON_COLON,	KC_ENT
    )
};



// Layer LEDs act as binary indication of current layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _OTHER:
	writePinLow(PLEX_LED_0);
	writePinHigh(PLEX_LED_2);
        break;
    case _V6:
	writePinLow(PLEX_LED_2);
	writePinHigh(PLEX_LED_0);
        break;
    default: //  for any other layers, or the default layer
	writePinLow(PLEX_LED_2);
	writePinLow(PLEX_LED_0);
        break;
    }
  return state;
}



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
                SEND_STRING("ffs ");
            }
            return false;
            break;
        case OHFFS:
            if (record->event.pressed) {
                SEND_STRING("oh ffs ");
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

        case COLON_COLON:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
            break;
        case ONETWENTYSEVEN:
            if (record->event.pressed) {
                SEND_STRING("/127");
            }
            return false;
            break;

        case GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m \"");
            }
            return false;
            break;
        case GIT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push\n");
            }
            return false;
            break;
        case GIT_ADD:
            if (record->event.pressed) {
                SEND_STRING("git add ");
            }
            return false;
            break;
        case GIT_DIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff\n");
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
