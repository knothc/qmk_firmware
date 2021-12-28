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

// MT(mod, kc) MOD_TAP. acts like a modifier when held, and a regular keycode when tapped.

// LT(layer, kc) LAYER_TAP. momentarily activates layer when held, and sends kc when tapped

// MO(layer) - momentarily activates layer. As soon as you let go of the key, the layer is deactivated.


#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

// Left-hand home row mods
#define HRM_A  LSFT_T(KC_A)
#define HRM_S  CTL_T(KC_S)
#define HRM_D  ALT_T(KC_D)
#define HRM_F  CMD_T(KC_F)

// Right-hand home row mods
#define HRM_J    RCMD_T(KC_J)
#define HRM_K    ALT_T(KC_K)
#define HRM_L    CTL_T(KC_L)
#define HRM_SCLN LSFT_T(KC_SCLN)

// Layer definitions
enum layers {
    _QWERTY = 0,
    _LOWER,
    _NAV,
    _RAISE,
    _ADJUST
};

// Macro Declarations
enum custom_keycodes {
  FWD_DEL_WORD = SAFE_RANGE,
  BCK_DEL_WORD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Base Layer: QWERTY
     *
     * ,-------------------------------------------.                              ,--------------------------------------------.
     * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  BSPC   |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+---------|
     * |   TAB  |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ñ  |  ' ?    |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+---------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |Alfred| BTT  |  |LShift|  BTT |  N   |  M   | ,  ; | . :  | -  _ |  RShift |
     * `----------------------+------+------+------+------+------|  |------+--------+------+------+------+---------------------'
     *                        | CTRL |      | CMD  |      |      |  | Enter| Space| NAV  | CMD  | ALT   |
     *                        |      | ALT  |      | Lower| ENT  |  | Lower| Raise|      |      |       |
     *                        `----------------------------------'  `-----------------------------------'
     */
    [_QWERTY] = LAYOUT(
      LT(_RAISE, KC_ESC), KC_Q,  KC_W,     KC_E,    KC_R,    KC_T,                                                                                       KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,     KC_BSPC,
      LT(_NAV, KC_TAB),   HRM_A, HRM_S,    HRM_D,   HRM_F,   KC_G,                                                                                       KC_H,     HRM_J,   HRM_K,   HRM_L,  HRM_SCLN, ES_QUOT,
      KC_LSFT,            KC_Z,  KC_X,     KC_C,    KC_V,    KC_B, LCTL(KC_SPC),  OSM(MOD_LCTL|MOD_LALT),    KC_LSFT,            OSM(MOD_LCTL|MOD_LALT), KC_N,     KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                                 KC_LCTRL, KC_LALT, KC_LGUI,       LT(_LOWER, KC_BSPC), KC_ENT,              LT(_LOWER, KC_ENT), LT(_RAISE, KC_SPC),     MO(_NAV), KC_RGUI, KC_RALT
    ),


    /*
     * Lower Layer: Symbols
     *
     * ,------------------------------------------.                              ,-------------------------------------------.
     * |       |  @   |      |      |  =   |  +   |                              |   |  |  {   |  }   |  =   |  `   |  DEL   |
     * |-------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |       |  !   |  "   |  #   |  $   |  %   |                              |  &   |  (   |  )   |  /   |   ?  |  ´ ¨   |
     * |-------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------| 
     * |       |  <   |  >   |      |  *   |  -   |      |      |  |      |      |  ¬   |  [   |  ]   |      | - _  |        |
     * `---------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                       |      |      |      |      |      |  |      |      |      |      |      |
     *                       |      |      |      |      |      |  |      |      |      |      |      |
     *                       `----------------------------------'  `----------------------------------'
     */
    [_LOWER] = LAYOUT(
       _______, ES_AT,   _______,   _______, ES_EQL,  ES_PLUS,                                        ES_PIPE, ES_LCBR, ES_RCBR, ES_EQL, KC_LBRC, KC_DEL,
       _______, ES_EXLM, ES_DQUO,   ES_HASH, ES_DLR,  ES_PERC,                                        ES_AMPR, ES_LPRN, ES_RPRN, ES_SLSH, ES_QUES, KC_QUOT,
       _______, KC_GRV,  S(KC_GRV), _______, ES_ASTR, ES_MINS, _______, _______,    _______, _______, ES_NOT,  ES_LBRC, ES_RBRC, _______, ES_MINS, _______,
                                    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
     ),


    /*
     * Raise Layer: Number keys & media
     *
     * ,-------------------------------------------.                              ,---------------------------------------------.
     * |        |      | Prev | Play | Next |      |                              |      | Vol- | Vol+   | Mute |      |        |
     * |--------+------+------+------+------+------|                              |------+------+--------+------+------+--------|
     * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8     |  9   |  0   |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+--------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |CTRL+SPC|      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+--------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |        |
     *                        |      |      |      |      |      |  |      |      |      |      |        |
     *                        `----------------------------------'  `------------------------------------'
     */
    [_RAISE] = LAYOUT(
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                        _______, KC_VOLD,      KC_VOLU, KC_MUTE, _______, _______,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,         KC_8,    KC_9,    KC_0,    _______,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, RCTL(KC_SPC), _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),





    /*
    * Navigation Layer: Arrows, navigation, text macros
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [_NAV] = LAYOUT(
      _______, _______, _______,    BCK_DEL_WORD,  FWD_DEL_WORD,   _______,                                _______, LCMD(KC_LEFT), KC_UP,   LCMD(KC_RIGHT), KC_HOME, KC_DEL,
      _______, KC_LSFT, KC_LSFT,    LALT(KC_LEFT), LALT(KC_RIGHT), _______,                                _______, KC_LEFT,       KC_DOWN, KC_RIGHT,       KC_END,  _______,
      _______, _______, LCMD(KC_X), LCMD(KC_C),    LCMD(KC_V),     _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
                                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),





    /*
     * Adjust Layer: Function keys, LED modes
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJUST] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Macro Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case FWD_DEL_WORD:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT) SS_TAP(X_BSPC));
            return false;
        }
        break;

    case BCK_DEL_WORD:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LSFT) SS_UP(X_LALT) SS_TAP(X_BSPC));
            return false;
        }
        break;
    }
    return true;
};

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case FWD_DEL_WORD: {
        if (record->event.pressed) {
            //SEND_STRING(SS_DOWN(KC_K)SS_DOWN(KC_DEL));
            //SEND_STRING("ASDF!!!");
            //  return false;
            return MACRO(D(LSFT), D(LALT), T(RIGHT), T(DEL), U(LSFT), U(LALT), END);
        }
    }

    case BCK_DEL_WORD: {
      if (record->event.pressed) {
          //SEND_STRING(LSA(KC_RIGHT) SS_DOWN(KC_DEL));
          SEND_STRING("ASDF!!!");
          return false;
      }
    }
  }
  return MACRO_NONE;
};
*/

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("knothc\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("UPPER\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
