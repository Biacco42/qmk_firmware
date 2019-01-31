#include QMK_KEYBOARD_H

enum keyboard_layers {
  BASE = 0,
  META,
  GAME,
  BIAC,
  BMETA,
};

// Custom #defined keycodes (shorter macros for readability)
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_biacco(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC, KC_BSLS, KC_JYEN,
  KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RO,   KC_RSFT,
  KC_LCTL, KC_LGUI, TG(BIAC),         RCTL_T(KC_SPC),   KC_BSPC, LT(META, KC_ENT), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TG(GAME)
),

[META] = LAYOUT_biacco(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______,          _______,          _______, _______,          _______, _______, _______, _______, _______
),

[GAME] = LAYOUT_biacco(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC, KC_BSLS, KC_JYEN,
  KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RO,   KC_RSFT,
  KC_LCTL, KC_LGUI, TG(BIAC),         KC_SPC,           KC_BSPC, KC_ENT,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
),

[BIAC] = LAYOUT_biacco(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
  KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Q,    KC_Y,    KC_G,    KC_D,    KC_M,    KC_F,    KC_RBRC, KC_BSLS, KC_JYEN,
  KC_LALT, KC_A,    KC_O,    KC_E,    KC_I,    KC_U,    KC_B,    KC_N,    KC_T,    KC_R,    KC_S,    KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_W,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SLSH, KC_RO,   KC_RSFT,
  KC_LCTL, KC_LGUI, _______,          RCTL_T(KC_SPC),   KC_BSPC, LT(BMETA, KC_ENT),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TG(BMETA)
),

[BMETA] = LAYOUT_biacco(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______,          _______,          _______, _______,          _______, _______, _______, _______, _______
)

};
