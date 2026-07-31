//=============================================================================
// File: ActionManager.cpp
// Commit: 4
//=============================================================================

#include "ActionManager.h"

#include "Queue.h"
#include "ProfileManager.h"
#include "HIDManager.h"

static ProfileManager Profile;

void ActionManager::begin()
{
    Profile.begin();
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
        Action action = mapEventToAction(event);

        if (action.type == ActionType::None)
        {
            continue;
        }

        if (hidManager != nullptr)
        {
            hidManager->execute(action);
        }
    }
}

Action ActionManager::mapEventToAction(const Event& event)
{
    Action action;

    switch (event.type)
    {
        case EventType::EncoderClockwise:
            action.type = Profile.getClockwiseAction();
            action.value = event.value;
            break;

        case EventType::EncoderCounterClockwise:
            action.type = Profile.getCounterClockwiseAction();
            action.value = event.value;
            break;

        case EventType::ButtonPressed:
            action.type = Profile.getButtonAction();
            action.value = 1;
            break;

        default:
            action.type = ActionType::None;
            action.value = 0;
            break;
    }

    return action;
}
