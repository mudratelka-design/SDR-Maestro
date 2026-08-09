//=============================================================================
// File: ProfileManager.h
// Commit: 11
// Version: 0.3.0
//=============================================================================

#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include <Arduino.h>

#include "Config.h"
#include "Types.h"
#include "Events.h"

// Holds PROFILE_COUNT independent button layouts (profile 0 = OpenWebRX
// default from OpenWebRXProfile.cpp, others start empty) and tracks which
// one is currently active. ActionManager only ever asks for the active
// profile's bindings via getAction(); the web config UI (WebConfigServer)
// reads/writes specific profiles by index via getProfileAction() /
// setProfileActions(), regardless of which one is active.
class ProfileManager
{
public:
    void begin();

    // What the ACTIVE profile says encoder/eventType should do.
    KeyAction getAction(uint8_t encoder, EventType eventType) const;

    uint8_t activeProfileIndex() const;
    void setActiveProfile(uint8_t profile);

    // Display name for profile [0, PROFILE_COUNT).
    const char* profileName(uint8_t profile) const;

    // Read/write a specific profile's bindings (not necessarily the active
    // one) - used by the web config UI.
    KeyAction getProfileAction(uint8_t profile, uint8_t encoder, EventType eventType) const;

    void setProfileActions(
        uint8_t profile,
        const KeyAction clockwise[],
        const KeyAction counterClockwise[],
        const KeyAction shortPress[],
        const KeyAction longPress[]);

private:
    KeyAction clockwiseAction[PROFILE_COUNT][ENCODER_COUNT];
    KeyAction counterClockwiseAction[PROFILE_COUNT][ENCODER_COUNT];
    KeyAction shortPressAction[PROFILE_COUNT][ENCODER_COUNT];
    KeyAction longPressAction[PROFILE_COUNT][ENCODER_COUNT];

    uint8_t activeProfile = 0;
};

extern ProfileManager ProfileManagerInstance;

#endif
