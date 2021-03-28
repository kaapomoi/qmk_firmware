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

#include <timer.h>
#include "snow.h"

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


#define FRAME_TIME 40

volatile uint16_t frame_timer = 0;


typedef union {
  uint32_t raw;
  struct {
    uint32_t     rng_seed;
  };
} user_config_t;

user_config_t user_config;


enum layers {
    _QWERTY = 0,
    _SYMBOLS,
    _NAVIGATION,
    _NUMBERS,
    _GAMER
};

enum custom_keycodes {
    K_COPY = SAFE_RANGE,
    K_PSTE,
    K_CUT,
    K_UNDO,
    K_REDO,
    K_RGBE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  + ?   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;    |  ä     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Ctrl   |   Z  |   X  |   C  |   V  |   B  |LShift|LCtrl |  |num/sb|AltGr |   N  |   M  | , ;  | . :  | -  _ |  ö     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *  *                     | GUI  | TAB  |  BSPC| Space| Enter|  | Enter| Bksp | Tab  | Del  | Enter|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_ESC , FI_Q,   FI_W,   FI_E,   FI_R,   FI_T,                                                      FI_Y,    FI_U,    FI_I,    FI_O,   FI_P,    FI_PLUS,
      KC_LSFT, FI_A,   FI_S,   FI_D,   FI_F,   FI_G,                                                      FI_H,    FI_J,    FI_K,    FI_L,   FI_SCLN, FI_ADIA,
      KC_LCTL, FI_Z,   FI_X,   FI_C,   FI_V,   FI_B,   KC_LSFT,   KC_LCTL,  LT(_NUMBERS, KC_SPC), KC_RALT, FI_N,    FI_M,    FI_COMM, FI_DOT, FI_MINS, FI_ODIA,
      KC_LGUI, KC_TAB, MT(MOD_LALT, KC_BSPC), LT(_SYMBOLS, KC_SPC), LT(_NAVIGATION, KC_ENT),        LT(_SYMBOLS, KC_ENT), LT(_NAVIGATION, KC_BSPC), KC_TAB,  KC_DEL, KC_ENT
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |   '  |  "   |   <  |   >  |    \ |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  §   |  $   |  (   |  )   |  #   |                              |   +  |  -   |  /   |  *   |  %   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  |   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  ´   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+---------------
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
      _______, FI_EXLM, FI_AT,   FI_LCBR, FI_RCBR, FI_PIPE,                                     FI_QUOT, FI_DQUO, FI_LABK, FI_RABK, FI_BSLS, _______,
      _______, FI_SECT, FI_DLR,  FI_LPRN, FI_RPRN, FI_HASH,                                     FI_PLUS, FI_MINS, FI_SLSH, FI_ASTR, FI_PERC, _______,
      _______, FI_PIPE, FI_CIRC, FI_LBRC, FI_RBRC, FI_TILD, _______, _______, _______, _______, FI_AMPR, FI_EQL,  FI_COMM, FI_DOT,  FI_ACUT, _______,
                                 _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),

    // this is a test of the kyria coding possibilities:
    /*
        int main(void){
            int x = 10;
            int arr[5] !@{}|
            §$()#
            
        }
    */
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | Copy |                              |      | Left | Up   | Right| Home |   PgUp |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |  Cut | Paste|      |      |  |      |      |      | Left | Down | Right|  End |   PgDn |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT(
      _______, FI_1, 	  FI_2,    FI_3,    FI_4,    FI_5,                                      FI_6,    FI_7,    FI_8,    FI_9,    FI_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, K_COPY,                                     _______, KC_LEFT, KC_UP,   KC_RGHT, KC_HOME, KC_PGUP,
      _______, _______, K_UNDO, K_REDO, K_CUT  , K_PSTE, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , KC_PGDN,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
 
 /*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RBGEnabl| SAT  |   7  |  8   |   9  |      |                              | F9   |  F10 |  F11 |  F12 |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  HUE |   4  |  5   |   6  |      |                              |  F5  |  F6  |  F7  |  F8  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | VAL  |   1  |  2   |   3  |      |RGBMOD| RGBE |  |      |      |   F1 |   F2 |   F3 |   F4 |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  0   |      |      |      |  |      |      |   0  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = LAYOUT(
      RGB_TOG, RGB_SAI, FI_7, FI_8, FI_9, _______,                                     KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
      _______, RGB_HUI, FI_4, FI_5, FI_6, _______,                                     KC_F5, KC_F6, KC_F7, KC_F8,    _______, _______,
      _______, RGB_VAI, FI_1, FI_2, FI_3, _______, RGB_MOD, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F4,    _______, _______,
                        TG(_GAMER), FI_0, _______, _______, _______, _______, _______, _______, _______, _______
    ),
 /*
 * Gamer Layer: Gamer / space doesnt have hold function
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
      KC_ESC , FI_Q,   FI_W,   FI_E,   FI_R,   FI_T,                                               FI_Y,    FI_U,    FI_I,    FI_O,   FI_P,    FI_PLUS,
      KC_LSFT, FI_A,   FI_S,   FI_D,   FI_F,   FI_G,                                               FI_H,    FI_J,    FI_K,    FI_L,   FI_SCLN, FI_ADIA,
      KC_LCTL, FI_Z,   FI_X,   FI_C,   FI_V,   FI_B,   KC_LSFT,   KC_LCTL,  TG(_GAMER), KC_RALT,  FI_N,    FI_M,    FI_COMM, FI_DOT, FI_MINS, FI_ODIA,
               KC_LGUI, KC_TAB, KC_LALT,       KC_SPC, LT(_NAVIGATION, KC_ENT),  LT(_SYMBOLS,  KC_ENT),  KC_BSPC,         KC_TAB,  KC_DEL,  KC_ENT
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

const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_RED}       // Light all red
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CYAN}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM navigation_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_GREEN}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM numbers_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_YELLOW}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM gamer_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM k_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    qwerty_layer,
    symbols_layer,    // Overrides caps lock layer
    navigation_layer,    // Overrides other layers
    numbers_layer,     // Overrides other layers
    gamer_layer
);

void keyboard_post_init_user(void){
    user_config.raw = eeconfig_read_user();

    snow_init(user_config.rng_seed);

    user_config.rng_seed = rand();

    eeconfig_update_user(user_config.raw);
    frame_timer = timer_read();
    rgblight_layers = k_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NAVIGATION));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _GAMER));
    return state;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}
 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case K_COPY:
            if (record->event.pressed) {
                tap_code16(C(FI_C));
            }
            break;
        case K_PSTE:
            if (record->event.pressed) {
                tap_code16(C(FI_V));
            }
            break;
        case K_CUT:
            if (record->event.pressed) {
                tap_code16(C(FI_X));
            }
            break;
        case K_UNDO:
            if (record->event.pressed) {
                tap_code16(C(FI_Z));
            }
            break;
        case K_REDO:
            if (record->event.pressed) {
                tap_code16(C(FI_Y));
            }
            break;
    }
    return true;
};

static void render_sakura(void){
    // 'sakura', 128x64px
    static const char PROGMEM sakurabmp[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x40, 0x88, 0x67, 0x1e, 
        0x8e, 0x62, 0x41, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x58, 0xf0, 0x70, 0xd0, 0xac, 
        0x84, 0x42, 0x61, 0xb0, 0xf8, 0x50, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x40, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x38, 0x80, 0xe0, 0x38, 0x0e, 0x07, 0x32, 0xf1, 0x29, 
        0x51, 0x01, 0x03, 0x00, 0x83, 0x40, 0x20, 0x10, 0x00, 0x08, 0x04, 0x4e, 0x83, 0xc5, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x70, 0x8f, 0xe0, 0x5d, 0x62, 0x52, 0xd0, 
        0x48, 0x40, 0x20, 0x20, 0x00, 0x30, 0x5c, 0x34, 0x48, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x60, 0x50, 
        0x90, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x01, 0x00, 0x00, 0x80, 0x80, 0x60, 0x20, 0x10, 
        0x18, 0x0c, 0x07, 0x09, 0x08, 0x00, 0x0c, 0x08, 0x04, 0x14, 0x06, 0x27, 0x04, 0x04, 0x02, 0x04, 
        0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 
        0xc0, 0xa0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x10, 0x18, 0x10, 0x08, 0x08, 0x0c, 0x04, 0x03, 0x01, 0xc1, 0x80, 0x40, 0x40, 0x00, 0x00, 0x01, 
        0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0xc0, 0xc0, 0xe0, 0x70, 0xfd, 0x4f, 0x22, 0x61, 
        0x31, 0x30, 0x10, 0x38, 0x28, 0x28, 0x24, 0x24, 0x24, 0x66, 0x43, 0x41, 0x40, 0x60, 0x60, 0xe0, 
        0xf0, 0xb0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 
        0x20, 0x10, 0x18, 0x8c, 0x8a, 0x94, 0xd6, 0xc2, 0x41, 0x41, 0x41, 0x62, 0x41, 0x20, 0x20, 0x18, 
        0x20, 0x20, 0x38, 0x7c, 0x5c, 0xf8, 0x78, 0x58, 0x20, 0x10, 0x20, 0x30, 0x28, 0x18, 0x25, 0x32, 
        0x23, 0x17, 0x30, 0x60, 0x30, 0x20, 0x50, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x0f, 0x1a, 0x27, 0x62, 0x86, 0x03, 0x06, 0x07, 0x07, 0x04, 0x06, 0x04, 0x0c, 0x0c, 0x0c, 0x1e, 
        0x1e, 0x0f, 0x1e, 0x16, 0x1b, 0x1b, 0x11, 0x13, 0x11, 0x10, 0x30, 0x10, 0x30, 0x10, 0x30, 0x30, 
        0x70, 0x20, 0xb0, 0x20, 0x30, 0x20, 0x30, 0x20, 0x60, 0x20, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xe1, 
        0x60, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x30, 0x18, 0x1c, 0x0e, 0x07, 0x07, 0x02, 
        0x03, 0x01, 0x03, 0x01, 0x15, 0x05, 0x02, 0x02, 0x02, 0x04, 0x08, 0x28, 0x38, 0xf8, 0x78, 0x28, 
        0x20, 0x40, 0x40, 0xc0, 0xa0, 0xc0, 0x00, 0xf0, 0x70, 0xb8, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x01, 0x01, 0x02, 0x0a, 0x34, 0x1c, 0x04, 0x08, 0x12, 0x22, 0x24, 0x04, 0x09, 0x03, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x02, 0x06, 0x05, 0x03, 0x05, 0x05, 0x19, 0x7b, 0x52, 0x22, 0x00, 0x02, 0x04, 
        0x04, 0x09, 0x07, 0x1f, 0x0f, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(sakurabmp, sizeof(sakurabmp));
}
         
// static void render_status(void) { 
//     // QMK Logo and version information
    
//     // x:0 y:7 rows
//     oled_set_cursor(0, 7);
//     switch (get_highest_layer(layer_state)) {
//         case _QWERTY:
//             oled_write_P(PSTR("default"), false);
//             break;
//         case _SYMBOLS:
//             oled_write_P(PSTR("symbols"), false);
//             break;
//         case _NAVIGATION:
//             oled_write_P(PSTR("navigation"), false);
//             break;
//         case _NUMBERS:
//             oled_write_P(PSTR("numbers"), false);
//             break;
//         case _GAMER:
//             oled_write_P(PSTR("gamer"), false);
//             break;
//         default:
//             oled_write_P(PSTR("Undefined"), false);
//             break;
//     }
    
// }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // Renders the current keyboard state (layer, lock, caps, scroll, etc)

        uint16_t frame_elapsed = 0;

        frame_elapsed = timer_elapsed(frame_timer);

        if (frame_elapsed > (FRAME_TIME)) {
            render_sakura();
            snow_animate();
            frame_timer = timer_read32();
        }

        //render_status();

    } else {
        uint16_t frame_elapsed = 0;

        frame_elapsed = timer_elapsed(frame_timer);

        if (frame_elapsed > (FRAME_TIME)) {
            render_sakura();
            snow_animate();
            frame_timer = timer_read32();
        }
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