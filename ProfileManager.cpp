//=============================================================================
// File: ProfileManager.cpp
// Commit: 3
//=============================================================================

#include "ProfileManager.h"
#include "OpenWebRXProfile.h"

static OpenWebRXProfile Profile;

void ProfileManager::begin()
{
    Profile.begin();

    clockwiseAction = Profile.getClockwiseAction();
    counterClockwiseAction = Profile.getCounterClockwiseAction();
    buttonAction = Profile.getButtonAction();
}

ActionType ProfileManager::getClockwiseAction() const
{
    return clockwiseAction;
}

ActionType ProfileManager::getCounterClockwiseAction() const
{
    return counterClockwiseAction;
}

ActionType ProfileManager::getButtonAction() const
{
    return buttonAction;
}
