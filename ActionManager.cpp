//=============================================================================
// File: ActionManager.cpp
// Commit: 7
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
            action.type =
                ProfileManagerInstance.getClockwiseAction(event.encoder);
            action.value = event.value;
            break;

        case EventType::EncoderCounterClockwise:
            action.type =
                ProfileManagerInstance.getCounterClockwiseAction(event.encoder);
            action.value = event.value;
            break;

        case EventType::ButtonPressed:
            action.type =
                ProfileManagerInstance.getButtonAction(event.encoder);
            action.value = 1;
            break;

        case EventType::ButtonLongPressed:
            action.type =
                ProfileManagerInstance.getLongButtonAction(event.encoder);
            action.value = 1;
            break;

        default:
            action.type = ActionType::None;
            action.value = 0;
            break;
    }

    return action;
}