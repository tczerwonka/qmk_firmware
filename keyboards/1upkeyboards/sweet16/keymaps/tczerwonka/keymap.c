/* T Czerwonka WO9U - 1upkeyboards sweet16 macropad */
/* configuration for ham use and some other stuff   */

/* make 1upkeyboards/sweet16/v1:tczerwonka:avrdude */

#include QMK_KEYBOARD_H

#define _HAM 		0
#define _KEYPAD 	1
#define _UTILITY	2

#define PLEX_LED_0	D7
#define PLEX_LED_1	E6
#define PLEX_LED_2	B4
#define PLEX_LED_3	B5

enum custom_keycodes {
  GIT_DIFF = SAFE_RANGE,
  GIT_PULL,
  GIT_PUSH,
  GIT_COMMIT,
  SIG1,
  MU,
  FLIP,
  SHRUG,
  OMEGA
};


/* base layer */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HAM] = LAYOUT_ortho_4x4(
        LSFT(KC_F16),	LSFT(KC_F10),  	KC_VOLU,   	TO(_KEYPAD),
        LSFT(KC_F17), 	LSFT(KC_F11),  	KC_VOLD,   	LSFT(KC_F9),
        LALT(KC_N), 	LSFT(KC_F13),  	LSFT(KC_F14),  	A(KC_TAB),
        LALT(KC_H), 	LALT(KC_E), 	LSFT(KC_F15), 	LALT(KC_N)	
    ),
/* second layer -- mostly a standard numeric keypad */
    [_KEYPAD] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   TO(_UTILITY),
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_PLUS,
        KC_0, KC_DOT, KC_MINS, KC_ENT
    ),
/* third layer -- some macros and unicode entries */
    [_UTILITY] = LAYOUT_ortho_4x4(
        MU,		OMEGA,   	SIG1,		TO(_HAM),
        GIT_DIFF, 	GIT_COMMIT,  	GIT_PUSH,	GIT_PULL,
        FLIP, 		SHRUG,		UC(0x223F),	UC(0x2213),
        UC(0x2218), 	UC(0x2205),	UC(0X2260),	KC_ENT
    )
};



// Layer LEDs act as binary indication of current layer
// with two LEDs and opposite polarities this could be
// a charlieplexed sort of arrangement
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _KEYPAD:
	writePinLow(PLEX_LED_0);
	writePinHigh(PLEX_LED_2);
        break;
    case _UTILITY:
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
        case GIT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull\n");
            }
            return false;
            break;
        case GIT_DIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff\n");
            }
            return false;
            break;
        case MU:
            if (record->event.pressed) {
                send_unicode_string("μ");
            }
            return false;
            break;
        case OMEGA:
            if (record->event.pressed) {
                send_unicode_string("Ω");
            }
            return false;
            break;
        case SIG1:
            if (record->event.pressed) {
                SEND_STRING("Tim Czerwonka\n608-239-3696 (c)\n");
            }
            return false;
            break;
        case FLIP:
            if (record->event.pressed) {
		send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
            }
            return false;
            break;
        case SHRUG:
            if (record->event.pressed) {
		send_unicode_string("¯\\_(ツ)_/¯");
            }
            return false;
            break;
    }
    return true;
}

//not used but a possibility with the extra pins
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
