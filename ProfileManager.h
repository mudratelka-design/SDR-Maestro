//=============================================================================
// File: ProfileManager.h
// Commit: 7
//=============================================================================

#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include "Types.h"

class ProfileManager
{
public:
    void begin();

    ActionType getClockwiseAction(uint8_t encoder) const;
    ActionType getCounterClockwiseAction(uint8_t encoder) const;
    ActionType getButtonAction(uint8_t encoder) const;
    ActionType getLongButtonAction(uint8_t encoder) const;

private:
    ActionType clockwiseAction[ENCODER_COUNT];
    ActionType counterClockwiseAction[ENCODER_COUNT];
    ActionType buttonAction[ENCODER_COUNT];
    ActionType longButtonAction[ENCODER_COUNT];
};

extern ProfileManager ProfileManagerInstance;

#endif	