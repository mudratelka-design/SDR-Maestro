//=============================================================================
// File: OpenWebRXProfile.cpp
// Commit: 3
//=============================================================================

#include "OpenWebRXProfile.h"

void OpenWebRXProfile::begin()
{
}

ActionType OpenWebRXProfile::getClockwiseAction() const
{
    return ActionType::FrequencyUp;
}

ActionType OpenWebRXProfile::getCounterClockwiseAction() const
{
    return ActionType::FrequencyDown;
}

ActionType OpenWebRXProfile::getButtonAction() const
{
    return ActionType::ToggleMute;
}
