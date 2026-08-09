//=============================================================================
// File: ProfileManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "ProfileManager.h"

#include "OpenWebRXProfile.h"

ProfileManager ProfileManagerInstance;

void ProfileManager::begin()
{
    OpenWebRXProfile::load(
        clockwiseAction,
        counterClockwiseAction,
        shortPressAction,
        longPressAction);
}

KeyAction ProfileManager::getAction(uint8_t encoder, EventType eventType) const
{
    if (encoder >= ENCODER_COUNT)
    {
        return KeyAction{};
    }

    switch (eventType)
    {
        case EventType::EncoderClockwise:
            return clockwiseAction[encoder];

        case EventType::EncoderCounterClockwise:
            return counterClockwiseAction[encoder];

        case EventType::ButtonPressed:
            return shortPressAction[encoder];

        case EventType::ButtonLongPressed:
            return longPressAction[encoder];

        case EventType::ButtonReleased:
        case EventType::None:
        default:
            return KeyAction{};
    }
}
