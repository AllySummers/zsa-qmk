enum tap_dances {
    TD_CAPS
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
};
