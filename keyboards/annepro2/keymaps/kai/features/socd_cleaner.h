// Copyright 2024 Google LLC
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

enum socd_cleaner_resolution {
    SOCD_CLEANER_OFF,
    SOCD_CLEANER_LAST,
    SOCD_CLEANER_NEUTRAL,
    SOCD_CLEANER_0_WINS,
    SOCD_CLEANER_1_WINS,
    SOCD_CLEANER_NUM_RESOLUTIONS,
};

typedef struct {
    uint8_t keys[2];
    uint8_t resolution;
    bool held[2];
} socd_cleaner_t;

bool process_socd_cleaner(uint16_t keycode, keyrecord_t* record,
                          socd_cleaner_t* state);

extern bool socd_cleaner_enabled;

#ifdef __cplusplus
}
#endif
