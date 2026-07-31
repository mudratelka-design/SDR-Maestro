//=============================================================================
// File: ButtonManager.cpp
// Commit: 2
//=============================================================================

#include <Arduino.h>

#include "ButtonManager.h"
#include "Queue.h"
#include "Events.h"

#ifndef BUTTON_PIN
#define BUTTON_PIN 3
#endif

void ButtonManager::begin()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    lastState = digitalRead(BUTTON_PIN);
}

void ButtonManager::update()
{
    bool state = digitalRead(BUTTON_PIN);

    if (state != lastState)
    {
        Event event;

        if (!state)
        {
            event.type = EventType::ButtonPressed;
        }
        else
        {
            event.type = EventType::ButtonReleased;
        }

        EventQueue.push(event);

        lastState = state;
    }
}
