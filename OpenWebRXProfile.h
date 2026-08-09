//=============================================================================
// File: OpenWebRXProfile.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef OPENWEBRX_PROFILE_H
#define OPENWEBRX_PROFILE_H

#include <Arduino.h>

#include "Config.h"
#include "Types.h"

class OpenWebRXProfile
{
public:
    // Fills in, per encoder, what turnRight / turnLeft / short press /
    // long press should send. This is the ONE place to edit when you
    // define your own button layout later.
    static void load(
        KeyAction clockwise[],
        KeyAction counterClockwise[],
        KeyAction shortPress[],
        KeyAction longPress[]);
};

#endif
