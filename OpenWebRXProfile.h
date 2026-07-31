//=============================================================================
// File: OpenWebRXProfile.h
// Commit: 3
//=============================================================================

#ifndef OPENWEBRX_PROFILE_H
#define OPENWEBRX_PROFILE_H

#include "Types.h"

class OpenWebRXProfile
{
public:
    void begin();

    ActionType getClockwiseAction() const;
    ActionType getCounterClockwiseAction() const;
    ActionType getButtonAction() const;
};

#endif
