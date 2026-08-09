//=============================================================================
// File: ButtonManager.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>

#include "Config.h"

class ButtonManager
{
public:
    void begin();
    void update();

private:
    bool lastState[ENCODER_COUNT];

    uint32_t lastChangeTime[ENCODER_COUNT];
    uint32_t pressTime[ENCODER_COUNT];

    bool longPressReported[ENCODER_COUNT];
};

#endif
