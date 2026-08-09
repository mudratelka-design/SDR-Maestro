//=============================================================================
// File: ActionManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "ActionManager.h"

#include "Queue.h"
#include "ProfileManager.h"
#include "HIDManager.h"

ActionManager ActionManagerInstance;

void ActionManager::begin()
{
}

void ActionManager::attachHID(HIDManager* hid)
{
    hidManager = hid;
}

void ActionManager::update()
{
    Event event;

    while (EventQueue.pop(event))
    {
        const KeyAction action = ProfileManagerInstance.getAction(event.encoder, event.type);

        if (action.type == KeyType::None)
        {
            continue;
        }

        if (hidManager != nullptr)
        {
            hidManager->execute(action);
        }
    }
}
