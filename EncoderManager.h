//=============================================================================
// File: EncoderManager.h
// Commit: 7
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
    int lastStateA[ENCODER_COUNT];
};

#endif