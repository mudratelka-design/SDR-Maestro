//=============================================================================
// File: ProfileManager.h
// Commit: 3
//=============================================================================

#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include "Types.h"

class ProfileManager
{
public:
    void begin();

    ActionType getClockwiseAction() const;
    ActionType getCounterClockwiseAction() const;
    ActionType getButtonAction() const;

private:
    ActionType clockwiseAction;
    ActionType counterClockwiseAction;
    ActionType buttonAction;
};

#endif
