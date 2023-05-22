/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "config.h"
#include "version.h"
#include "custom_shift/custom_shift_keys.h"
#include "tap_dance/tap_dance_setup.c"
#include "tap_dance/dance_caps_caps_word.c"
#include "tap_dance/tap_dances.c"

static bool transport_connected = 0;

enum layers {
    BASE,
    FN_1,
    FN_2,
    GM_1,
    GM_2
};

const custom_shift_key_t custom_shift_keys[] = {
    {  KC_9   ,    KC_9     }, // Shift 9 is 9
    {  KC_0   ,    KC_0     }, // Shift 0 is 0,
    { KC_LPRN ,   KC_LBRC   }, // Shift ( is [
    { KC_RPRN ,   KC_RBRC   }, // Shift ) is ]
    { KC_LCBR ,   KC_QUOT   }, // Shift { is '
    { KC_RCBR ,   KC_DQUO   }, // Shift { is "
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ BASE ] = LAYOUT_moonlander(
        KC_PGUP     , KC_1        , KC_2        , KC_3        , KC_4        , KC_5        , KC_MINS     ,                             KC_EQL      , KC_6        , KC_7        , KC_8        , KC_9        , KC_0        , KC_PSCR     ,
        KC_PGDN     , KC_Q        , KC_W        , KC_E        , KC_R        , KC_T        , KC_LCBR     ,                             KC_RCBR     , KC_Y        , KC_U        , KC_I        , KC_O        , KC_P        , KC_BSLS     ,
        TD(TD_CAPS) , KC_A        , KC_S        , KC_D        , KC_F        , KC_G        , KC_LPRN     ,                             KC_RPRN     , KC_H        , KC_J        , KC_K        , KC_L        , KC_SCLN     , KC_GRV      ,
        KC_LSFT     , KC_Z        , KC_X        , KC_C        , KC_V        , KC_B        ,                                                         KC_N        , KC_M        , KC_COMM     , KC_DOT      , KC_SLSH     , KC_RSFT     ,
        KC_LCTL     , KC_LGUI     , KC_LALT     , KC_LEFT     , KC_UP       ,               KC_ESC      ,                             KC_NO       ,               KC_DOWN     , KC_RIGHT    , KC_RALT     , KC_RGUI     , KC_RCTL     ,
                                                                              KC_SPC      , KC_TAB      , MO(FN_1)    , MO(FN_2)    , KC_ENT      , KC_BSPC
    ),
    [ FN_1 ] = LAYOUT_moonlander(
        KC_TRNS     , KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5       , KC_F6       ,                             KC_F7       , KC_F8       , KC_F9       , KC_F10      , KC_F11      , KC_F12      , KC_TRNS     ,
        KC_TRNS     , KC_F13      , KC_F14      , KC_F15      , KC_F16      , KC_F17      , KC_F18      ,                             KC_F19      , KC_F20      , KC_F21      , KC_F22      , KC_F23      , KC_F24      , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                             KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                                                         KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_MPRV     , KC_VOLU     ,               KC_TRNS     ,                             KC_TRNS     ,               KC_VOLD     , KC_MNXT     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
                                                                              KC_INS      , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_DEL
    ),
    [ FN_2 ] = LAYOUT_moonlander(
        QK_BOOT     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                             KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , EE_CLR      ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                             KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                             KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,                                                         KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,               KC_TRNS     ,                             KC_TRNS     ,               KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
                                                                              KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS
    ),
    [ GM_1 ] = LAYOUT_halfmoon(
        KC_ESC      , KC_1        , KC_2        , KC_3        , KC_4        , KC_5        , KC_GRV      ,
        KC_PSCR     , KC_Q        , KC_W        , KC_E        , KC_R        , KC_T        , KC_Y        ,
        KC_ENT      , KC_A        , KC_S        , KC_D        , KC_F        , KC_G        , KC_H        ,
        KC_LSFT     , KC_Z        , KC_X        , KC_C        , KC_V        , KC_B        ,
        KC_LGUI     , KC_LALT     , KC_LCTL     , KC_N        , KC_M        ,               KC_ESC      ,
                                                                              KC_SPC      , KC_TAB      , MO(GM_2)
    ),
    [ GM_2 ] = LAYOUT_halfmoon(
        KC_PGUP     , KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5       , KC_F6       ,
        KC_PGDN     , KC_F7       , KC_F8       , KC_F9       , KC_F10      , KC_F11      , KC_F12      ,
        KC_RSFT     , KC_BSPC     , KC_MNXT     , KC_HOME     , KC_UP       , KC_END      , KC_DEL      ,
        KC_END      , KC_K        , KC_MPRV     , KC_LEFT     , KC_DOWN     , KC_RGHT     ,
        KC_RGUI     , KC_RALT     , KC_RCTL     , KC_L        , KC_TRNS     ,               KC_WH_U     ,
                                                                              KC_BTN1     , KC_WH_D     , KC_BTN2
    )
};

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [BASE] = { {42,255,255}, {42,255,255}, {51,102,255}, {51,102,255}, {51,102,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {51,102,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {51,102,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {42,255,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {42,255,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {0,168,255}, {0,168,255}, {0,168,255}, {93,255,255}, {93,255,255}, {170,255,255}, {114,255,255}, {114,255,255}, {0,168,255}, {0,168,255}, {51,102,255}, {51,102,255}, {205,241,223}, {139,255,255}, {0,168,255}, {0,168,255}, {51,102,255}, {205,241,223}, {139,255,255}, {139,255,255}, {0,168,255}, {51,102,255}, {205,241,223}, {139,255,255}, {139,255,255}, {0,168,255}, {42,255,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {42,255,255}, {205,241,223}, {139,255,255}, {139,255,255}, {139,255,255}, {0,168,255}, {0,168,255}, {0,168,255}, {93,255,255}, {93,255,255}, {170,255,255}, {0,0,0} },
    [FN_1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {114,255,255}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {114,255,255}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {93,255,255}, {0,0,0}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {114,255,255}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {114,255,255}, {24,214,255}, {24,214,255}, {0,0,0}, {0,0,0}, {24,214,255}, {24,214,255}, {0,0,0}, {93,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },
    [FN_2] = { {114,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {114,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0} },
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

void set_layer_color(int layer) {
    uint8_t modifiers = get_mods();

    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (modifiers == MOD_MASK_SHIFT && (
            /* Shift Symbols */
            i == 5 ||
            i == 10 ||
            i == 15 ||
            i == 20 ||
            i == 25 ||
            i == 29 ||
            i == 30 ||
            i == 31 ||
            i == 37 ||
            i == 38 ||
            i == 43 ||
            i == 44 ||
            i == 49 ||
            i == 51 ||
            i == 54 ||
            i == 56 ||
            i == 61 ||
            i == 65 ||
            i == 66 ||
            i == 67
        )) {
            rgb_matrix_set_color(i, RGB_RED);
        } else if (i == 2 && is_caps_word_on()) {
            rgb_matrix_set_color(i, RGB_WHITE);
        } else if (i == 2 && host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(i, RGB_RED);
        } else {
            HSV hsv = {
                .h = pgm_read_byte(&ledmap[layer][i][0]),
                .s = pgm_read_byte(&ledmap[layer][i][1]),
                .v = pgm_read_byte(&ledmap[layer][i][2]),
            };
            if (!hsv.h && !hsv.s && !hsv.v) {
                rgb_matrix_set_color( i, 0, 0, 0 );
            } else {
                RGB rgb = hsv_to_rgb( hsv );
                float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
                rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
            }
        }

  }
}

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    if (layer < GM_1) {
        switch (layer) {
            case BASE:
                set_layer_color(BASE);
                break;
            case FN_1:
                set_layer_color(FN_1);
                break;
            case FN_2:
                set_layer_color(FN_2);
                break;
            default:
                break;
        }
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    bool LED_1 = false;
    bool LED_2 = false;
    bool LED_3 = false;
    bool LED_4 = false;

    if (transport_connected) {
        switch (get_highest_layer(state)) {
            case BASE:
                LED_1 = true;
            case FN_1:
                LED_1 = true;
                LED_2 = true;
                break;
            case FN_2:
                LED_1 = true;
                LED_2 = true;
                LED_3 = true;
                break;
            default:
                break;
            }
    } else {
        switch (get_highest_layer(state)) {
            case GM_1:
                LED_3 = true;
                break;
            case GM_2:
                LED_2 = true;
                LED_3 = true;
                break;
            default:
                break;
            }
    }

    ML_LED_1(LED_1);
    ML_LED_2(LED_2);
    ML_LED_3(LED_3);
    ML_LED_4(LED_4);

    return state;
}

void housekeeping_task_user(void) {
    transport_connected = is_transport_connected();
    bool gaming_enabled = IS_LAYER_ON(GM_1) || IS_LAYER_ON(GM_2);

    if (transport_connected && gaming_enabled) {
        layer_clear();
        layer_on(BASE);
    } else if (!transport_connected && !gaming_enabled) {
        layer_clear();
        layer_on(GM_1);
    }
}

void led_update_ports(led_t led_state) {
    ML_LED_5(led_state.caps_lock);
    ML_LED_6(is_caps_word_on());
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }

  return true;
}
