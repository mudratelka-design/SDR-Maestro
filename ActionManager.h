//=============================================================================
// File: ActionManager.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "Events.h"
#include "Types.h"

class HIDManager;

class ActionManager
{
public:
    void begin();
    void update();

    void attachHID(HIDManager* hid);

private:
    HIDManager* hidManager = nullptr;
};

extern ActionManager ActionManagerInstance;

#endif
