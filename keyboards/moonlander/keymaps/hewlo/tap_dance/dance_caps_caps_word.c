void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    int td_state = cur_dance(state);

    if (td_state == SINGLE_TAP) {
        if (host_keyboard_led_state().caps_lock) {
            register_code(KC_CAPS);
        } else if (is_caps_word_on()) {
            caps_word_off();
        } else {
            caps_word_on();
        }
    } else if (td_state == DOUBLE_TAP) {
        register_code(KC_CAPS);
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    int td_state = cur_dance(state);

    if (td_state == SINGLE_TAP || td_state == DOUBLE_TAP) {
        unregister_code(KC_CAPS);
    }
}

