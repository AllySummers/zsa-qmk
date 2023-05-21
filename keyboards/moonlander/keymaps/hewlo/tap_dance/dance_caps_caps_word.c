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

