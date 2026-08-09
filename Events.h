//=============================================================================
// File: Events.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>

enum class EventType : uint8_t
{
    None = 0,

    EncoderClockwise,        // "turnRight"
    EncoderCounterClockwise, // "turnLeft"

    ButtonPressed,      // short press (released before the long-press threshold)
    ButtonReleased,     // raw release edge, currently unused by any profile
    ButtonLongPressed   // held past BUTTON_LONG_PRESS_MS
};

struct Event
{
    EventType type = EventType::None;

    uint8_t encoder = 0;

    int32_t value = 0;
};

#endif
