/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include <stdio.h>

// Row 1
#define FI_SECT KC_GRV  // §
#define FI_1    KC_1    // 1
#define FI_2    KC_2    // 2
#define FI_3    KC_3    // 3
#define FI_4    KC_4    // 4
#define FI_5    KC_5    // 5
#define FI_6    KC_6    // 6
#define FI_7    KC_7    // 7
#define FI_8    KC_8    // 8
#define FI_9    KC_9    // 9
#define FI_0    KC_0    // 0
#define FI_PLUS KC_MINS // +
#define FI_ACUT KC_EQL  // ´ (dead)
// Row 2
#define FI_Q    KC_Q    // Q
#define FI_W    KC_W    // W
#define FI_E    KC_E    // E
#define FI_R    KC_R    // R
#define FI_T    KC_T    // T
#define FI_Y    KC_Y    // Y
#define FI_U    KC_U    // U
#define FI_I    KC_I    // I
#define FI_O    KC_O    // O
#define FI_P    KC_P    // P
#define FI_ARNG KC_LBRC // Å
#define FI_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define FI_A    KC_A    // A
#define FI_S    KC_S    // S
#define FI_D    KC_D    // D
#define FI_F    KC_F    // F
#define FI_G    KC_G    // G
#define FI_H    KC_H    // H
#define FI_J    KC_J    // J
#define FI_K    KC_K    // K
#define FI_L    KC_L    // L
#define FI_ODIA KC_SCLN // Ö
#define FI_ADIA KC_QUOT // Ä
#define FI_QUOT KC_NUHS // '
// Row 4
#define FI_LABK KC_NUBS // <
#define FI_Z    KC_Z    // Z
#define FI_X    KC_X    // X
#define FI_C    KC_C    // C
#define FI_V    KC_V    // V
#define FI_B    KC_B    // B
#define FI_N    KC_N    // N
#define FI_M    KC_M    // M
#define FI_COMM KC_COMM // ,
#define FI_DOT  KC_DOT  // .
#define FI_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ½ │ ! │ " │ # │ ¤ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ^ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define FI_HALF S(FI_SECT) // ½
#define FI_EXLM S(FI_1)    // !
#define FI_DQUO S(FI_2)    // "
#define FI_HASH S(FI_3)    // #
#define FI_CURR S(FI_4)    // ¤
#define FI_PERC S(FI_5)    // %
#define FI_AMPR S(FI_6)    // &
#define FI_SLSH S(FI_7)    // /
#define FI_LPRN S(FI_8)    // (
#define FI_RPRN S(FI_9)    // )
#define FI_EQL  S(FI_0)    // =
#define FI_QUES S(FI_PLUS) // ?
#define FI_GRV  S(FI_ACUT) // ` (dead)
// Row 2
#define FI_CIRC S(FI_DIAE) // ^ (dead)
// Row 3
#define FI_ASTR S(FI_QUOT) // *
// Row 4
#define FI_RABK S(FI_LABK) // >
#define FI_SCLN S(FI_COMM) // ;
#define FI_COLN S(FI_DOT)  // :
#define FI_UNDS S(FI_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ $ │ € │   │ { │ [ │ ] │ } │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define FI_AT   ALGR(FI_2)    // @
#define FI_PND  ALGR(FI_3)    // £
#define FI_DLR  ALGR(FI_4)    // $
#define FI_EURO ALGR(FI_5)    // €
#define FI_LCBR ALGR(FI_7)    // {
#define FI_LBRC ALGR(FI_8)    // [
#define FI_RBRC ALGR(FI_9)    // ]
#define FI_RCBR ALGR(FI_0)    // }
#define FI_BSLS ALGR(FI_PLUS) // (backslash)
// Row 2
#define FI_TILD ALGR(FI_DIAE) // ~ (dead)
// Row 4
#define FI_PIPE ALGR(FI_LABK) // |
#define FI_MICR ALGR(FI_M)    // µ

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMBERS,
    _GAMER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Ctrl   |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *  *                     | GUI  | Del  |  BSPC| Space| Enter|  | Enter| Bksp | Tab  | Del  | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_ESC ,       KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
      KC_LSFT,       KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_PLUS,
      KC_LCTL,       KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,   KC_LCTL, LT(_NUMBERS, KC_SPC), KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
             KC_LGUI, KC_TAB, MT(MOD_LALT, KC_BSPC), LT(_LOWER, KC_SPC), LT(_RAISE, KC_ENT),        LT(_LOWER, KC_ENT), LT(_RAISE, KC_BSPC), KC_TAB,  KC_DEL, KC_ENT
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+---------------
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, _______, KC_BSLS, _______, _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL,  KC_SCLN, _______, _______, _______
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              |      | Left | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      |      |      | Down |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     _______, KC_LEFT, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, _______, _______, KC_DOWN, KC_RGHT, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
 
 /*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |   7  |  8   |   9  |      |                              |      |   7  |   8  |   9  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |   4  |  5   |   6  |      |                              |      |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |   1  |  2   |   3  |      |      |      |  |      |      |   F1 |   F2 |   F3 |   3  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  0   |      |      |      |  |      |      |   0  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = LAYOUT(
      RGB_TOG, RGB_SAI, KC_7, KC_8, KC_9, _______,                                     KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
      _______, RGB_HUI, KC_4, KC_5, KC_6, _______,                                     KC_F5, KC_F6, KC_F7, KC_F8, _______, _______,
      _______, RGB_VAI, KC_1, KC_2, KC_3, _______, RGB_MOD, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F4, _______, _______,
                         TG(_GAMER), KC_0, _______, _______, _______, _______, _______, _______, _______, _______
    ),
 /*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|       
 * | Ctrl   |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *  *                     | GUI  | Del  |  BSPC| Space| Enter|  | Enter| Bksp | Tab  | Del  | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMER] = LAYOUT(
      KC_ESC ,       KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
      KC_LSFT,                  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_PLUS,
      KC_LCTL,                  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,   KC_LCTL, TG(_GAMER), KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
             KC_LGUI, KC_TAB, KC_LALT, KC_SPC, LT(_RAISE, KC_ENT), LT(_LOWER, KC_ENT), KC_BSPC, KC_TAB,  KC_DEL, KC_ENT
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

// WPM-responsive animation stuff here             
static void render_status(void) { 
    // QMK Logo and version information
    // render_qmk_logo();
    oled_set_cursor(0,6);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("        Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("        Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("        Raise\n"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("        Numbers\n"), false);
            break;
        case _GAMER:
            oled_write_P(PSTR("        Gamer\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
} 

void oled_task_user(void) {
    if (is_keyboard_master()) {
        //render_skull();
        //oled_set_cursor(7,6);
        render_status();
     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {

    }
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (!clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
}
#endif