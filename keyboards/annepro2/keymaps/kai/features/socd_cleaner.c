// Copyright 2024 Google LLC
// SPDX-License-Identifier: Apache-2.0

#include "socd_cleaner.h"

#ifdef __cplusplus
extern "C" {
#endif

bool socd_cleaner_enabled = false;

static void update_key(uint8_t keycode, bool press) {
    if (press) {
        add_key(keycode);
    } else {
        del_key(keycode);
    }
}

bool process_socd_cleaner(uint16_t keycode, keyrecord_t* record,
                          socd_cleaner_t* state) {
    if (!socd_cleaner_enabled || !state->resolution ||
        (keycode != state->keys[0] && keycode != state->keys[1])) {
        return true;
    }
    const uint8_t i = (keycode == state->keys[1]);
    const uint8_t opposing = i ^ 1;

    state->held[i] = record->event.pressed;

    if (state->held[opposing]) {
        switch (state->resolution) {
            case SOCD_CLEANER_LAST:
                update_key(state->keys[opposing], !state->held[i]);
                break;
            case SOCD_CLEANER_NEUTRAL:
                update_key(state->keys[opposing], !state->held[i]);
                send_keyboard_report();
                return false;
            case SOCD_CLEANER_0_WINS:
            case SOCD_CLEANER_1_WINS:
                if (opposing == (state->resolution - SOCD_CLEANER_0_WINS)) {
                    return false;
                } else {
                    update_key(state->keys[opposing], !state->held[i]);
                }
                break;
        }
    }
    return true;
}
