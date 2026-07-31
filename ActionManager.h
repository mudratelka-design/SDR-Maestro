//=============================================================================
// File: ActionManager.h
// Commit: 7
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
    Action mapEventToAction(const Event& event);

    HIDManager* hidManager = nullptr;
};

extern ActionManager ActionManagerInstance;

#endif