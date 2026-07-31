//=============================================================================
// File: ProfileManager.cpp
// Commit: 7
//=============================================================================

#include "ProfileManager.h"

#include "Config.h"
#include "OpenWebRXProfile.h"

ProfileManager ProfileManagerInstance;

void ProfileManager::begin()
{
    OpenWebRXProfile::load(
        clockwiseAction,
        counterClockwiseAction,
        buttonAction,
        longButtonAction);
}

ActionType ProfileManager::getClockwiseAction(uint8_t encoder) const
{
    return clockwiseAction[encoder];
}

ActionType ProfileManager::getCounterClockwiseAction(uint8_t encoder) const
{
    return counterClockwiseAction[encoder];
}

ActionType ProfileManager::getButtonAction(uint8_t encoder) const
{
    return buttonAction[encoder];
}

ActionType ProfileManager::getLongButtonAction(uint8_t encoder) const
{
    return longButtonAction[encoder];
}