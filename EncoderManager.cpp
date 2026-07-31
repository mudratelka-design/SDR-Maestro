//=============================================================================
// File: EncoderManager.cpp
// Commit: 2
//=============================================================================

#include <Arduino.h>

#include "EncoderManager.h"
#include "Queue.h"
#include "Events.h"

#ifndef ENCODER_PIN_A
#define ENCODER_PIN_A 1
#endif

#ifndef ENCODER_PIN_B
#define ENCODER_PIN_B 2
#endif

void EncoderManager::begin()
{
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);

    lastState = digitalRead(ENCODER_PIN_A);
}

void EncoderManager::update()
{
    int currentState = digitalRead(ENCODER_PIN_A);

    if (currentState != lastState)
    {
        Event event;

        if (digitalRead(ENCODER_PIN_B) != currentState)
        {
            event.type = EventType::EncoderClockwise;
            event.value = 1;
        }
        else
        {
            event.type = EventType::EncoderCounterClockwise;
            event.value = -1;
        }

        EventQueue.push(event);

        lastState = currentState;
    }
}
