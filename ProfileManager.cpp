//=============================================================================
// File: ProfileManager.cpp
// Commit: 11
// Version: 0.3.0
//=============================================================================

#include "ProfileManager.h"

#include <stdio.h>

#include "OpenWebRXProfile.h"
#include "StorageManager.h"
#include "Logger.h"

ProfileManager ProfileManagerInstance;

namespace
{
    const char* PROFILE_NAMES[PROFILE_COUNT] =
    {
        "OpenWebRX", "Profile 2", "Profile 3", "Profile 4", "Profile 5"
        // NOTE: this list is sized/written for PROFILE_COUNT == 5. If you
        // change ENCODER_COUNT in Config.h, add/remove names to match.
    };
}

void ProfileManager::begin()
{
    for (uint8_t p = 0; p < PROFILE_COUNT; p++)
    {
        for (uint8_t e = 0; e < ENCODER_COUNT; e++)
        {
            clockwiseAction[p][e] = KeyAction{};
            counterClockwiseAction[p][e] = KeyAction{};
            shortPressAction[p][e] = KeyAction{};
            longPressAction[p][e] = KeyAction{};
        }
    }

    // Profile 0's compiled-in defaults (the working OpenWebRX example
    // bindings). Loaded first so profile 0 behaves exactly as before this
    // feature existed, unless it's since been customized via the web UI.
    OpenWebRXProfile::load(
        clockwiseAction[0],
        counterClockwiseAction[0],
        shortPressAction[0],
        longPressAction[0]);

    // Any web-UI customization saved to flash overrides the in-RAM values
    // above, per profile, per encoder, per event - a field that was never
    // saved is simply left at whatever it already was (KeyType::None, or
    // the OpenWebRX default for profile 0).
    for (uint8_t p = 0; p < PROFILE_COUNT; p++)
    {
        StorageManagerInstance.loadProfile(
            p,
            clockwiseAction[p],
            counterClockwiseAction[p],
            shortPressAction[p],
            longPressAction[p]);
    }

    activeProfile = 0;
}

KeyAction ProfileManager::getAction(uint8_t encoder, EventType eventType) const
{
    return getProfileAction(activeProfile, encoder, eventType);
}

KeyAction ProfileManager::getProfileAction(uint8_t profile, uint8_t encoder, EventType eventType) const
{
    if (profile >= PROFILE_COUNT || encoder >= ENCODER_COUNT)
    {
        return KeyAction{};
    }

    switch (eventType)
    {
        case EventType::EncoderClockwise:
            return clockwiseAction[profile][encoder];

        case EventType::EncoderCounterClockwise:
            return counterClockwiseAction[profile][encoder];

        case EventType::ButtonPressed:
            return shortPressAction[profile][encoder];

        case EventType::ButtonLongPressed:
            return longPressAction[profile][encoder];

        case EventType::ButtonReleased:
        case EventType::None:
        default:
            return KeyAction{};
    }
}

uint8_t ProfileManager::activeProfileIndex() const
{
    return activeProfile;
}

void ProfileManager::setActiveProfile(uint8_t profile)
{
    if (profile >= PROFILE_COUNT)
    {
        return;
    }

    activeProfile = profile;

    char buf[48];
    snprintf(buf, sizeof(buf), "Active profile set to %u (%s).", profile, profileName(profile));
    LoggerInstance.info(buf);
}

const char* ProfileManager::profileName(uint8_t profile) const
{
    if (profile >= PROFILE_COUNT)
    {
        return "?";
    }

    return PROFILE_NAMES[profile];
}

void ProfileManager::setProfileActions(
    uint8_t profile,
    const KeyAction clockwise[],
    const KeyAction counterClockwise[],
    const KeyAction shortPress[],
    const KeyAction longPress[])
{
    if (profile >= PROFILE_COUNT)
    {
        return;
    }

    for (uint8_t e = 0; e < ENCODER_COUNT; e++)
    {
        clockwiseAction[profile][e] = clockwise[e];
        counterClockwiseAction[profile][e] = counterClockwise[e];
        shortPressAction[profile][e] = shortPress[e];
        longPressAction[profile][e] = longPress[e];
    }

    StorageManagerInstance.saveProfile(
        profile,
        clockwiseAction[profile],
        counterClockwiseAction[profile],
        shortPressAction[profile],
        longPressAction[profile]);
}
