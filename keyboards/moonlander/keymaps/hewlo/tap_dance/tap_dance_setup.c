enum tap_dance_state {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,  // Send two single taps.
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7,
    TRIPLE_SINGLE_TAP = 8,  // Send three single taps.
    UNKNOWN_DANCE     = 100,
};

/**
 * @brief Determines the state from tap dance state and converts to custom action
 * @returns Value of `tap_dance_state`
 */
int cur_dance (tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        }
        return SINGLE_HOLD; //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    }

    if (state->count == 2) {
        if (state->interrupted) {
            /*
            * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
            * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
            * keystrokes of the key, and not the 'double tap' action/macro.
            */
            return DOUBLE_SINGLE_TAP;
        }

        if (state->pressed) {
            return DOUBLE_HOLD;
        }

        return DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted) {
            return TRIPLE_SINGLE_TAP;
        }

        if (state->pressed) {
            return TRIPLE_HOLD;
        }

        return TRIPLE_TAP;
    }

    return UNKNOWN_DANCE;
}
