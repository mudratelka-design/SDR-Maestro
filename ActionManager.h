//=============================================================================
// File: ActionManager.h
// Commit: 3
//=============================================================================

#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "Events.h"
#include "Types.h"

class ActionManager
{
public:
    void begin();
    void update();

private:
    Action mapEventToAction(const Event& event);
};

#endif
