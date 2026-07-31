//=============================================================================
// File: ButtonManager.cpp
// Commit: 7
//=============================================================================

#include "ButtonManager.h"

#include "Queue.h"

void ButtonManager::begin()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        pinMode(ENCODERS[i].pinKey, INPUT);

        lastState[i] = digitalRead(ENCODERS[i].pinKey);

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
        const bool state = digitalRead(ENCODERS[i].pinKey);

        if (state != lastState[i])
        {
            if ((now - lastChangeTime[i]) >= BUTTON_DEBOUNCE_MS)
            {
                lastChangeTime[i] = now;
                lastState[i] = state;

                Event event;
                event.encoder = i;

                if (!state)
                {
                    pressTime[i] = now;
                    longPressReported[i] = false;

                    event.type = EventType::ButtonPressed;
                }
                else
                {
                    event.type = EventType::ButtonReleased;
                }

                EventQueue.push(event);
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