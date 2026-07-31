//=============================================================================
// File: Events.h
// Commit: 2
//=============================================================================

#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>

enum class EventType : uint8_t
{
    None = 0,

    EncoderClockwise,
    EncoderCounterClockwise,

    ButtonPressed,
    ButtonReleased
};

struct Event
{
    EventType type = EventType::None;
    int32_t value = 0;
};

#endif
