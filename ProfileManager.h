//=============================================================================
// File: ProfileManager.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include <Arduino.h>

#include "Config.h"
#include "Types.h"
#include "Events.h"

class ProfileManager
{
public:
    void begin();

    // Looks up what a given encoder's event (turn/press/long-press) should
    // send. Returns a KeyAction with type == KeyType::None for anything not
    // bound to a key.
    KeyAction getAction(uint8_t encoder, EventType eventType) const;

private:
    KeyAction clockwiseAction[ENCODER_COUNT];        // turnRight
    KeyAction counterClockwiseAction[ENCODER_COUNT]; // turnLeft
    KeyAction shortPressAction[ENCODER_COUNT];
    KeyAction longPressAction[ENCODER_COUNT];
};

extern ProfileManager ProfileManagerInstance;

#endif
