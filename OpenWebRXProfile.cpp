//=============================================================================
// File: OpenWebRXProfile.cpp
// Commit: 7
//=============================================================================

#include "OpenWebRXProfile.h"

void OpenWebRXProfile::load(
    ActionType clockwise[],
    ActionType counterClockwise[],
    ActionType button[],
    ActionType longButton[])
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        clockwise[i] = ActionType::FrequencyUp;
        counterClockwise[i] = ActionType::FrequencyDown;
        button[i] = ActionType::ToggleMute;
        longButton[i] = ActionType::None;
    }
}