//=============================================================================
// File: Events.h
// Commit: 7
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
    ButtonReleased,
    ButtonLongPressed
};

struct Event
{
    EventType type = EventType::None;
    uint8_t encoder = 0;
    int32_t value = 0;
};

#endif