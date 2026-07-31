//=============================================================================
// File: Types.h
// Commit: 3
//=============================================================================

#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

enum class ActionType : uint8_t
{
    None = 0,

    FrequencyUp,
    FrequencyDown,

    VolumeUp,
    VolumeDown,

    GainUp,
    GainDown,

    ModeNext,
    ModePrevious,

    ToggleMute
};

struct Action
{
    ActionType type = ActionType::None;
    int32_t value = 0;
};

#endif
