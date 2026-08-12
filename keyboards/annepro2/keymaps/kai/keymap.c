/* Copyright 2021 OpenAnnePro community
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
#include "features/socd_cleaner.h"

enum anne_pro_layers {
    BASE,  // Default layer
    FN1,   // Navigation & F-keys
    FN2,   // Media, BT, RGB
};

enum custom_keycodes {
    SOCD_TOGG = SAFE_RANGE,  // Toggle SOCD cleaner on/off
};

// clang-format off
/*
 * Layer BASE
 * ,-----------------------------------------------------------------------------------------.
 * | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | Caps   |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl  |  GUI  |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
 * \-----------------------------------------------------------------------------------------/
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_60_ansi(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, LT(FN1,KC_NO), LT(FN2,KC_NO), KC_RCTL
),

/*
 * Layer FN1
 * ,-----------------------------------------------------------------------------------------.
 * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  Delete   |
 * |-----------------------------------------------------------------------------------------+
 * |       |     | UP  |     |     |     |     |     | UP  |     | PScr| Home| End |           |
 * |-----------------------------------------------------------------------------------------+
 * |        | Left| Down| Right|     |     |     | Left| Down| Right|PgUp |PgDn |             |
 * |-----------------------------------------------------------------------------------------+
 * |            |     |     |     |     |     |     |     |     | Ins | Del |               |
 * |-----------------------------------------------------------------------------------------+
 * |       |       |       |                                 |       |       | FN2  |       |
 * \-----------------------------------------------------------------------------------------/
 */
[FN1] = LAYOUT_60_ansi(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_UP,   _______, KC_PSCR, KC_HOME, KC_END,  _______,
    KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_DEL,  _______,
    _______, _______, _______,                            _______,                   _______, _______, MO(FN2), _______
),

/*
 * Layer FN2
 * ,-----------------------------------------------------------------------------------------.
 * |     | BT1 | BT2 | BT3 | BT4 |     |     |     |     | RGB Mod|RGB Tog|RGB V-|RGB V+|     |
 * |-----------------------------------------------------------------------------------------+
 * |       |     | VOLU|     |     |     |     |     | VOLU|     | PScr| Home| End |           |
 * |-----------------------------------------------------------------------------------------+
 * |        |SOCD | VolD| Next|     |     |     | Prev| VolD| Next | PgUp |PgDn |             |
 * |-----------------------------------------------------------------------------------------+
 * |            | BRIU|     |     |     |     |     |     |     | Ins | Del |               |
 * |-----------------------------------------------------------------------------------------+
 * |       | BRID |       |              Play              |       | FN1  |       |       |
 * \-----------------------------------------------------------------------------------------/
 */
[FN2] = LAYOUT_60_ansi(
    _______, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, _______, KC_AP_RGB_MOD, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, _______,
    _______, _______,    KC_VOLU,    _______,    _______,    _______, _______, _______, KC_VOLU,    _______,      KC_PSCR,       KC_HOME,       KC_END,        _______,
    SOCD_TOGG,KC_MPRV,   KC_VOLD,    KC_MNXT,    _______,    _______, _______, KC_MPRV,    KC_VOLD,      KC_MNXT,       KC_PGUP,       KC_PGDN,       _______,
    _______,             KC_BRIU,    _______,    _______,    _______, _______, _______, _______,    _______,      KC_INS,        KC_DEL,        _______,
    _______, KC_BRID,    _______,                                     KC_MPLY,                         _______,      MO(FN1),       _______,       _______
),
};
// clang-format on

// SOCD cleaner pairs for WASD gaming
socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};

// Use magic value so uninitialized/zeroed memory both mean "off"
// 0x42 = on, anything else = off
#define SOCD_MAGIC_ON 0x42
static uint8_t socd_state = 0x00;

// Update SOCD LED indicators (blue on A and D when enabled)
void update_socd_leds(void) {
    const ap2_led_t color = {.p.red = 0x00, .p.green = 0x00, .p.blue = 0xff, .p.alpha = 0xff};
    if (socd_state == SOCD_MAGIC_ON) {
        ap2_led_sticky_set_key(2, 1, color);  // A key
        ap2_led_sticky_set_key(2, 3, color);  // D key
    } else {
        ap2_led_unset_sticky_key(2, 1);
        ap2_led_unset_sticky_key(2, 3);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Only run SOCD filtering when explicitly toggled on
    if (socd_state == SOCD_MAGIC_ON) {
        if (!process_socd_cleaner(keycode, record, &socd_v)) { return false; }
        if (!process_socd_cleaner(keycode, record, &socd_h)) { return false; }
    }

    switch (keycode) {
        case SOCD_TOGG:
            if (record->event.pressed) {
                if (socd_state == SOCD_MAGIC_ON) {
                    socd_state = 0x00;
                    socd_cleaner_enabled = false;
                } else {
                    socd_state = SOCD_MAGIC_ON;
                    socd_cleaner_enabled = true;
                }
                update_socd_leds();
            }
            return false;
    }
    return true;
}

// The function to handle the caps lock logic
// It's called after the capslock changes state or after entering layers 1 and 2.
bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        // Set the caps-lock to red
        const ap2_led_t color = {.p.red = 0xff, .p.green = 0x00, .p.blue = 0x00, .p.alpha = 0xff};
        ap2_led_sticky_set_key(2, 0, color);
    } else {
        // Reset the capslock if there is no layer active
        ap2_led_unset_sticky_key(2, 0);
    }

    return true;
}
