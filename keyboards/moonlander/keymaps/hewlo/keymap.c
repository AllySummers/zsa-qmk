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
#include "version.h"

static bool transport_connected = 0;

enum layers {
    BASE,
    FN_1,
    FN_2,
    GM_1,
    GM_2
};

/*
    Description: Possible states for a given tap dance

    * SINGLE_HOLD   = 1: Activates while holding the key
    * SINGLE_TAP    = 2: Activates when pressing the key once
    * DOUBLE_TAP    = 3: Activates when pressing the key 2 times in quick succession
    * TRIPLE_TAP    = 4: Activates when pressing the key 3 times in quick succession
*/
enum tap_dance_state {
    SINGLE_HOLD = 1,
    SINGLE_TAP = 2,
    DOUBLE_TAP = 3,
    TRIPLE_TAP = 4,
};

enum tap_dances {
    TD_CAPS
};

/**
 * @brief Determines the state from tap dance state and converts to custom action
 * @returns Value of `tap_dance_state`
 */
int cur_dance(tap_dance_state_t *state) {
    if (state->pressed) {
        return SINGLE_HOLD;
    }
    if (state->count == 1) {
        return SINGLE_TAP;
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    }
    if (state->count == 3) {
        return TRIPLE_TAP;
    }

    return -1;
}

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    int td_state = cur_dance(state);

    switch (td_state) {
        case SINGLE_TAP:
            register_code(KC_CAPS);
            break;
        case DOUBLE_TAP:
            caps_word_on();
            break;
        default:
            break;
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    int td_state = cur_dance(state);

    switch (td_state) {
        case SINGLE_TAP:
            unregister_code(KC_CAPS);
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ BASE ] = LAYOUT_moonlander(
        KC_GRV       ,  KC_1         ,  KC_2         ,  KC_3         ,  KC_4         ,  KC_5         ,  KC_MINS      ,                                  KC_EQL       ,  KC_6         ,  KC_7         ,  KC_8         ,  KC_9         ,  KC_0         ,  KC_INS       ,
        KC_TAB       ,  KC_Q         ,  KC_W         ,  KC_E         ,  KC_R         ,  KC_T         ,  KC_LBRC      ,                                  KC_RBRC      ,  KC_Y         ,  KC_U         ,  KC_I         ,  KC_O         ,  KC_P         ,  KC_BSLS      ,
        TD(TD_CAPS)  ,  KC_A         ,  KC_S         ,  KC_D         ,  KC_F         ,  KC_G         ,  KC_ENT       ,                                  KC_BSPC      ,  KC_H         ,  KC_J         ,  KC_L         ,  KC_SCLN      ,  KC_QUOT      ,  KC_DEL       ,
        KC_LSFT      ,  KC_Z         ,  KC_X         ,  KC_C         ,  KC_V         ,  KC_B         ,                                                  KC_N         ,  KC_M         ,  KC_COMM      ,  KC_DOT       ,  KC_SLSH      ,  KC_RSFT      ,
        TT(FN_1)     ,  KC_PSCR      ,  KC_LGUI      ,  KC_LALT      ,  KC_LCTL      ,                  KC_SPC       ,                                  KC_SPC       ,                  KC_RCTL      ,  KC_RALT      ,  KC_RGUI      ,  KC_ESC       ,  TT(FN_2)     ,
                                                                                        KC_LSFT      ,  KC_UP        ,  KC_LEFT      ,  KC_RGHT      ,  KC_DOWN      ,  KC_ENT
    ),
    [ FN_1 ] = LAYOUT_moonlander(
        KC_TRNS      ,  KC_F1        ,  KC_F2        ,  KC_F3        ,  KC_F4        ,  KC_F5        ,  KC_F6        ,                                  KC_F7        ,  KC_F8        ,  KC_F9        ,  KC_F10       ,  KC_F11       ,  KC_F12       ,  KC_VOLU      ,
        KC_TRNS      ,  KC_F13       ,  KC_F14       ,  KC_F15       ,  KC_F16       ,  KC_F17       ,  KC_F18       ,                                  KC_F19       ,  KC_F20       ,  KC_F21       ,  KC_F22       ,  KC_F23       ,  KC_F24       ,  KC_VOLD      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                  KC_TRNS      ,  KC_MNXT      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_MNXT      ,  KC_MUTE      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_MPRV      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                  KC_PGUP      ,                                  KC_TRNS      ,                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,
                                                                                        KC_HOME      ,  KC_PGDN      ,  KC_END       ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS
    ),
    [ FN_2 ] = LAYOUT_moonlander(
        QK_BOOT      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  EE_CLR       ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                                                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,
        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,                  KC_TRNS      ,                                  KC_TRNS      ,                  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,
                                                                                        KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS      ,  KC_TRNS
    ),
    [ GM_1 ] = LAYOUT_halfmoon(
        KC_GRV       ,  KC_1         ,  KC_2         ,  KC_3         ,  KC_4         ,  KC_5         ,  KC_ESC       ,
        KC_PSCR      ,  KC_Q         ,  KC_W         ,  KC_E         ,  KC_R         ,  KC_T         ,  KC_Y         ,
        KC_ENT       ,  KC_A         ,  KC_S         ,  KC_D         ,  KC_F         ,  KC_G         ,  KC_H         ,
        KC_LSFT      ,  KC_Z         ,  KC_X         ,  KC_C         ,  KC_V         ,  KC_B         ,
        KC_LGUI      ,  KC_LALT      ,  KC_LCTL      ,  KC_N        ,   KC_M         ,                  KC_ESC       ,
                                                                                        KC_SPC       ,  KC_TAB       ,  MO(GM_2)
    ),
    [ GM_2 ] = LAYOUT_halfmoon(
        KC_PGUP      ,  KC_F1        ,  KC_F2        ,  KC_F3        ,  KC_F4        ,  KC_F5        ,  KC_F6        ,
        KC_PGDN      ,  KC_F7        ,  KC_F8        ,  KC_F9        ,  KC_F10       ,  KC_F11       ,  KC_F12       ,
        KC_RSFT      ,  KC_BSPC      ,  KC_MNXT      ,  KC_HOME      ,  KC_UP        ,  KC_END       ,  KC_DEL       ,
        KC_END       ,  KC_K         ,  KC_MPRV      ,  KC_LEFT      ,  KC_DOWN      ,  KC_RGHT      ,
        KC_RGUI      ,  KC_RALT      ,  KC_RCTL      ,  KC_L         ,  KC_TRNS      ,                  KC_WH_U      ,
                                                                                        KC_BTN1      ,  KC_WH_D      ,  KC_BTN2
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    if (transport_connected) {
        led_t led_state = host_keyboard_led_state();

        if (led_state.caps_lock) {
            ML_LED_6(true);
        } else {
            ML_LED_6(false);
        }

        switch (get_highest_layer(state)) {
            case FN_1:
                ML_LED_1(true);
                ML_LED_2(true);
                ML_LED_3(false);
                break;
            case FN_2:
                ML_LED_1(true);
                ML_LED_2(true);
                ML_LED_3(true);
                break;
            default:
                ML_LED_1(true);
                ML_LED_2(false);
                ML_LED_3(false);
                break;
            }
    } else {
        switch (get_highest_layer(state)) {
            case GM_1:
                ML_LED_1(false);
                ML_LED_2(false);
                ML_LED_3(true);
                break;
            case GM_2:
                ML_LED_1(false);
                ML_LED_2(true);
                ML_LED_3(true);
                break;
            default:
                ML_LED_1(false);
                ML_LED_2(false);
                ML_LED_3(false);
                break;
            }
    }
  return state;
}

void housekeeping_task_user(void) {
    transport_connected = is_transport_connected();

    layer_clear();
    if (transport_connected) {
        layer_on(BASE);
    } else {
        layer_on(GM_1);
    }
}
