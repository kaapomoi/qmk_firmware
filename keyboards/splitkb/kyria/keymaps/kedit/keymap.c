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
#include <stdio.h>
#include QMK_KEYBOARD_H
#include "quantum/raw_hid.h"

#include <timer.h>
#include <string.h>
#include "snow.h"
#include "todo.h"
#include "etch.h"

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


#define FRAME_TIME 60

void lenc_action(bool pressed);
void renc_pressed(void);
void lenc_c(void);
void lenc_cw(void);
void renc_c(void);
void renc_cw(void);

volatile uint16_t frame_timer = 0;
unsigned int keys_pressed = 0;

uint8_t should_reset_etch = 0;
bool ticker_list_dirty = true;

#define CMD_BUF_SZ 8
#define MAX_TICKERS 8
#define TICKER_DATA_SZ 21

char tickers[MAX_TICKERS][TICKER_DATA_SZ];
uint8_t current_ticker = 0;

typedef union {
  uint32_t raw;
  struct {
    uint32_t     rng_seed;
  };
} user_config_t;

user_config_t user_config;

enum enc_modes {
    ARROW,
    ETCH
} enc_mode;

enum layers {
    _QWERTY = 0,
    _SYMBOLS,
    _NUMBERS_AND_NAV,
    _MEDIA,
    _TODO,
    _TC_SYMBOLS,
    _TC_NUMBERS
};

enum custom_keycodes {
    K_COPY = SAFE_RANGE,
    K_PSTE,
    K_CUT,
    K_UNDO,
    K_REDO,
    K_RGBE,
    K_COLN,
    K_LENC,
    K_RENC,
    HI_OFF,
    HI_ON
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  + ?   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | :  ; |  Ä     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Ctrl   |   Z  |   X  |   C  |   V  |   B  |LShift|LCtrl |  | FKeys|AltGr |   N  |   M  | ,  ; | .  : | -  _ |  Ö     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *  *                     | GUI  | TAB  |  BSPC| Space| Enter|  | Enter| Bksp | Win  | Del  | Enter|
 *                        |      |      | Alt  |Symbol|NumNav|  |NumNav|NumNav|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_ESC , FI_Q,   FI_W,   FI_E,   FI_R,   FI_T,                                                                        FI_Y,    FI_U,    FI_I,    FI_O,    FI_P, FI_PLUS,
      KC_LSFT, FI_A,   FI_S,   FI_D,   FI_F,   FI_G,                                                                        FI_H,    FI_J,    FI_K,    FI_L,  K_COLN, FI_ADIA,
      KC_LCTL, FI_Z,   FI_X,   FI_C,   FI_V,   FI_B,   KC_LSFT,   KC_LCTL,                          MO(_MEDIA), KC_LSFT,    FI_N,    FI_M, FI_COMM,  FI_DOT, FI_MINS, FI_ODIA,
      K_LENC, KC_TAB, MT(MOD_LALT, KC_BSPC), LT(_SYMBOLS, KC_SPC), LT(_NUMBERS_AND_NAV, KC_ENT),    MO(_NUMBERS_AND_NAV), LT(_NUMBERS_AND_NAV, KC_BSPC), KC_LGUI,  KC_DEL, K_RENC
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |   '  |  "   |  <   |  >   |  \   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  &   |  $   |  (   |  )   |  #   |                              |   +  |  -   |  /   |  *   |  %   |  PgUp  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  |   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  ´   |  PgDn  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
      _______, FI_EXLM, FI_AT,   FI_LCBR, FI_RCBR, FI_PIPE,                                     FI_QUOT, FI_DQUO, FI_LABK, FI_RABK, FI_BSLS, _______,
      _______, FI_SECT, FI_DLR,  FI_LPRN, FI_RPRN, FI_HASH,                                     FI_PLUS, FI_MINS, FI_SLSH, FI_ASTR, FI_PERC, KC_PGUP,
      _______, FI_PIPE, FI_CIRC, FI_LBRC, FI_RBRC, FI_TILD, _______, _______, _______, _______, FI_AMPR, FI_EQL,  FI_COMM, FI_DOT,  FI_ACUT, KC_PGDN,
                                 K_LENC , _______, _______, _______, _______,  _______,  _______, _______, _______, K_RENC
    ),

/*
 * Raise Layer: Number keys, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |Insert|  7   |  8   |  9   |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   0  |  4   |  5   |  6   |      |                              | Left | Down |  Up  | Right|      |  PgUp  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | END  |  1   |  2   |  3   | End  |      | HID T|  |      |      |      |      |      |      |      |  PgDn  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LENC |  0   |      |      |      |  |      |      |      |      | RENC |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS_AND_NAV] = LAYOUT(
      _______,  KC_INS,   FI_7,   FI_8,   FI_9, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,    FI_0,   FI_4,   FI_5,   FI_6, _______,                                     KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, KC_PGUP,
      _______, KC_HOME,   FI_1,   FI_2,   FI_3,  KC_END, HI_OFF , HI_ON, _______, _______, _______, _______, _______, _______, _______, KC_PGDN,
                         K_LENC, FI_0, _______, _______, _______, _______, _______, _______, _______, K_RENC
    ),

 /*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RBGEnabl| SAT  |   7  |  8   |   9  |      |                              |   F9 |  F10 |  F11 |  F12 |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |RGBMode | HUE  |   4  |  5   |   6  |      |                              |   F5 |   F6 |   F7 |   F8 |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | VAL  |   1  |  2   |   3  |      |RGBMOD| RGBE |  |      |      |   F1 |   F2 |   F3 |   F4 |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MEDIA] = LAYOUT(
      RGB_TOG, RGB_SAI, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
      RGB_MOD, RGB_HUI, K_CUT  , K_COPY , K_PSTE , _______,                                     KC_F5, KC_F6 , KC_F7 , KC_F8 , _______, _______,
      _______, RGB_VAI, _______, _______, _______, _______, _______, TG(_TODO), _______, _______, KC_F1, KC_F2 , KC_F3 , KC_F4 , _______, _______,
                        K_LENC,  _______, _______, _______, _______, _______, _______, _______, _______, K_RENC
    ),

/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  + ?   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | :  ; |  Ä     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Ctrl   |   Z  |   X  |   C  |   V  |   B  |LShift|LCtrl |  | FKeys|AltGr |   N  |   M  | ,  ; | .  : | -  _ |  Ö     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *  *                     | GUI  | TAB  |  BSPC| Space| Enter|  | Enter| Bksp | Tab  | Del  | Enter|
 *                        |      |      | Alt  |Symbol|NumNav|  |NumNav|NumNav|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_TODO] = LAYOUT(
      KC_ESC , TC_Q,   TC_W,   TC_E,   TC_R,   TC_T,                                                                        TC_Y,    TC_U,    TC_I,    TC_O,    TC_P, TC_PLUS,
      KC_LSFT, TC_A,   TC_S,   TC_D,   TC_F,   TC_G,                                                                        TC_H,    TC_J,    TC_K,    TC_L, TC_COLN, FI_ADIA,
      KC_LCTL, TC_Z,   TC_X,   TC_C,   TC_V,   TC_B,   MO(_TC_SYMBOLS),   _______,                  MO(_MEDIA), KC_LSFT,    TC_N,    TC_M, TC_COMM,  TC_PERI, TC_MINU, FI_ODIA,
                               K_LENC, KC_TAB,MOD_LALT, TC_SPCE, TC_ENT,                   MO(_TC_NUMBERS), TC_BKSP, KC_TAB,  KC_DEL, K_RENC
    ),

/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |   '  |  "   |  <   |  >   |  \   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  &   |  $   |  (   |  )   |  #   |                              |   +  |  -   |  /   |  *   |  %   |  PgUp  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  |   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  ´   |  PgDn  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_TC_SYMBOLS] = LAYOUT(
      _______, TC_EXLM, TC_AT,   TC_OBRA, TC_CBRA, TC_VBAR,                                     TC_QUOT, TC_QUOT, TC_LT  , TC_GT  , TC_BKSL, TC_QUES,
      _______, FI_SECT, TC_DOLR, TC_OPAR, TC_CPAR, TC_HASH,                                     TC_PLUS, TC_MINU, TC_SLSH, TC_ASTE, TC_PERC, _______,
      _______, TC_VBAR, TC_CARE, TC_OBRE, TC_CRBE, TC_TILD, _______, _______, _______, _______, TC_AMPR, TC_EQ  , TC_COMM, TC_PERI, TC_GRAV, _______,
                                 K_LENC , _______, _______, _______, _______, _______, _______, _______, _______, K_RENC
    ),

/*
 * Raise Layer: Number keys, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |Insert|  7   |  8   |  9   |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   0  |  4   |  5   |  6   |      |                              | Left | Down |  Up  | Right|      |  PgUp  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | END  |  1   |  2   |  3   | End  |      |      |  |      |      |      |      |      |      |      |  PgDn  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LENC |  0   |      |      |      |  |      |      |      |      | RENC |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_TC_NUMBERS] = LAYOUT(
      _______, _______,   TC_7,   TC_8,   TC_9, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,    TC_0,   TC_4,   TC_5,   TC_6, _______,                                     TC_LEFT, TC_DOWN,   TC_UP, TC_RGHT, _______, _______,
      _______, _______,   TC_1,   TC_2,   TC_3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                         K_LENC,  TC_0, _______, _______, _______, _______, _______, _______, _______, K_RENC
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

void keyboard_post_init_user(void){
    user_config.raw = eeconfig_read_user();

    snow_init(user_config.rng_seed);
    user_config.rng_seed = rand();

    todo_init();

    eeconfig_update_user(user_config.raw);
    frame_timer = timer_read();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _TODO ||
        get_highest_layer(layer_state) == _TC_SYMBOLS ||
        get_highest_layer(layer_state) == _TC_NUMBERS) {
        return todo_handle_input(keycode, record);
    }

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
        case K_COLN:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT)
                {
                    tap_code16(FI_SCLN);
                }
                else
                {
                    tap_code16(FI_COLN);
                }
            }
            break;
        case K_LENC:
            if (record->event.pressed)
            {
                lenc_action(true);
            } else {
                lenc_action(false);
            }
            break;
        case K_RENC:
            if (record->event.pressed)
            {
                renc_pressed();
            }
            break;
        case HI_OFF:
            {
                if (record->event.pressed)
                {
                    char strr[] = "OFF";
                    uint8_t hid_size = 32;
                    uint8_t hid_data[hid_size];
                    memset(hid_data, 0, hid_size);
                    memcpy(hid_data, strr, strlen(strr) + 1);

                    raw_hid_send(hid_data, hid_size);
                }
            break;
            }
        case HI_ON:
            {
                if (record->event.pressed)
                {
                    char strr[] = "ON";
                    uint8_t hid_size = 32;
                    uint8_t hid_data[hid_size];
                    memset(hid_data, 0, hid_size);
                    memcpy(hid_data, strr, strlen(strr) + 1);

                    raw_hid_send(hid_data, hid_size);
                }
            break;
            }
        }

    if (record->event.pressed){
        keys_pressed++;
    }

    return true;
};


void clear_tickers(void) {
    for (uint8_t i = 0; i < MAX_TICKERS; ++i) {
        memset(tickers[i], 0x00, TICKER_DATA_SZ);
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Your code goes here
    // `data` is a pointer to the buffer containing the received HID report
    // `length` is the length of the report - always `RAW_EPSIZE`
    //t.price = *((float*) data + 1);
    //memcpy(&t.price, data, sizeof(float));

    char cmd_buf[CMD_BUF_SZ];
    memcpy(cmd_buf, data, CMD_BUF_SZ);

    if (strcmp(cmd_buf, "CLEAR") == 0){
        clear_tickers();
        current_ticker = 0;
    }else{
        memcpy(tickers[current_ticker], data, TICKER_DATA_SZ);
        ticker_list_dirty = true;

        current_ticker++;
        if (current_ticker > MAX_TICKERS){
            current_ticker = 0;
        }
    }
}

//static void render_sakura(void){
    //oled_write_raw_P(sakurabmp, sizeof(sakurabmp));
//}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (should_reset_etch)
        {
            etch_reset();
            should_reset_etch = 0;
        }

        if (enc_mode == ETCH)
        {
            etch_animate();
        }

        if (get_highest_layer(layer_state) == _TODO ||
            get_highest_layer(layer_state) == _TC_SYMBOLS ||
            get_highest_layer(layer_state) == _TC_NUMBERS) {
            todo_render();
            return false;
        }

        uint16_t frame_elapsed = 0;

        frame_elapsed = timer_elapsed(frame_timer);

        if (frame_elapsed > (FRAME_TIME) && enc_mode != ETCH) {
            //oled_clear();
            //render_sakura();
            //snow_animate();
            frame_timer = timer_read32();

            if (ticker_list_dirty){
                oled_clear();
                for (uint8_t i = 0; i < MAX_TICKERS; ++i) {
                    char ticker_str[16];
                    sprintf(ticker_str, "%s", tickers[i]);
                    oled_write_ln(ticker_str, false);
                }
                ticker_list_dirty = false;
            }
            /*
            char keys_pressed_dec_str[16];
            sprintf(keys_pressed_dec_str, "%d", keys_pressed);
            oled_write(keys_pressed_dec_str, false);
            */
        }

    } else {
        uint16_t frame_elapsed = 0;

        frame_elapsed = timer_elapsed(frame_timer);

        if (frame_elapsed > (FRAME_TIME)) {
            oled_clear();
            snow_animate();
            frame_timer = timer_read32();
            char keys_pressed_dec_str[16];
            sprintf(keys_pressed_dec_str, "%d", keys_pressed);
            oled_write(keys_pressed_dec_str, false);
        }
    }

    return false;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            lenc_c();
        } else {
            lenc_cw();
        }
    }
    else if (index == 1) {
        if (clockwise) {
            renc_c();
        } else {
            renc_cw();
        }
    }

    return false;
}
#endif

void lenc_action(bool pressed){
    if (get_highest_layer(layer_state) == _NUMBERS_AND_NAV) {
        enc_mode = ETCH;
        should_reset_etch = 1;
        etch_reset();
        return;
    }

    switch (enc_mode)
    {
    case ARROW:
        if (pressed) {
            register_code(KC_LGUI);
        } else {
            unregister_code(KC_LGUI);
        }
        break;
    case ETCH:
        etch_reset();
        break;
    default:
        break;
    }
}

void renc_pressed(void){
    if (get_highest_layer(layer_state) == _NUMBERS_AND_NAV) {
        enc_mode = ARROW;
        return;
    }

    switch (enc_mode)
    {
    case ARROW:
        tap_code16(KC_ENT);
        break;
    case ETCH:
        etch_init();
        break;
    default:
        break;
    }
}

void lenc_c(void){
    switch (enc_mode)
    {
    case ARROW:
        tap_code(KC_UP);
        break;
    case ETCH:
        etch_move_cursor(E_UP);
        break;
    }
}

void lenc_cw(void){
    switch (enc_mode)
    {
    case ARROW:
        tap_code(KC_DOWN);
        break;
    case ETCH:
        etch_move_cursor(E_DOWN);
        break;
    }
}

void renc_c(void){
    switch (enc_mode)
    {
    case ARROW:
        tap_code(KC_UP);
        break;
    case ETCH:
        etch_move_cursor(E_LEFT);
        break;
    }
}

void renc_cw(void){
    switch (enc_mode)
    {
    case ARROW:
        tap_code(KC_DOWN);
        break;
    case ETCH:
        etch_move_cursor(E_RIGHT);
        break;
    }
}

