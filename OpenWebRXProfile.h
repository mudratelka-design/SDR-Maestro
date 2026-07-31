//=============================================================================
// File: OpenWebRXProfile.h
// Commit: 7
//=============================================================================

#ifndef OPENWEBRX_PROFILE_H
#define OPENWEBRX_PROFILE_H

#include "Config.h"
#include "Types.h"

class OpenWebRXProfile
{
public:
    static void load(
        ActionType clockwise[],
        ActionType counterClockwise[],
        ActionType button[],
        ActionType longButton[]);
};

#endif