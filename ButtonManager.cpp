//=============================================================================
// File: ButtonManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// A short press is only reported on release, and only if the long-press
// threshold was never reached while the button was held. The original
// version fired the "pressed" event immediately on the falling edge and
// then ALSO fired "long pressed" later if held - so every long press
// double-fired both the short-press action and the long-press action.
//=============================================================================

#include "ButtonManager.h"

#include "Events.h"
#include "Queue.h"

void ButtonManager::begin()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        pinMode(ENCODERS[i].pinButton, INPUT);

        lastState[i] = digitalRead(ENCODERS[i].pinButton);

        lastChangeTime[i] = millis();
        pressTime[i] = 0;
        longPressReported[i] = false;
    }
}

void ButtonManager::update()
{
    const uint32_t now = millis();

    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        const bool state = digitalRead(ENCODERS[i].pinButton);

        if (state != lastState[i] && (now - lastChangeTime[i]) >= BUTTON_DEBOUNCE_MS)
        {
            lastState[i] = state;
            lastChangeTime[i] = now;

            if (!state)
            {
                // Falling edge: button just pressed. Don't fire an action
                // yet - wait to see whether this turns into a short press
                // (released early) or a long press (still held below).
                pressTime[i] = now;
                longPressReported[i] = false;
            }
            else
            {
                // Rising edge: button released. Only counts as a short
                // press if the long-press threshold was never reached.
                if (!longPressReported[i])
                {
                    Event event;
                    event.encoder = i;
                    event.type = EventType::ButtonPressed;

                    EventQueue.push(event);
                }
            }
        }

        if (!state &&
            !longPressReported[i] &&
            ((now - pressTime[i]) >= BUTTON_LONG_PRESS_MS))
        {
            longPressReported[i] = true;

            Event event;
            event.encoder = i;
            event.type = EventType::ButtonLongPressed;

            EventQueue.push(event);
        }
    }
}
