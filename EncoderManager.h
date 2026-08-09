//=============================================================================
// File: EncoderManager.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

#include <Arduino.h>

#include "Config.h"

class EncoderManager
{
public:
    void begin();
    void update();

private:
    uint8_t lastState[ENCODER_COUNT];
    int8_t  accumulator[ENCODER_COUNT];
};

#endif
