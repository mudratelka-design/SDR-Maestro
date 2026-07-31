//=============================================================================
// File: EncoderManager.cpp
// Commit: 6
//=============================================================================

#include "EncoderManager.h"

#include "Config.h"
#include "Queue.h"
#include "Events.h"

void EncoderManager::begin()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        pinMode(ENCODERS[i].pinA, INPUT);
        pinMode(ENCODERS[i].pinB, INPUT);

        lastStateA[i] = digitalRead(ENCODERS[i].pinA);
    }
}

void EncoderManager::update()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        int stateA = digitalRead(ENCODERS[i].pinA);

        if (stateA != lastStateA[i])
        {
            Event event;

            event.encoder = i;

            if (digitalRead(ENCODERS[i].pinB) != stateA)
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

            lastStateA[i] = stateA;
        }
    }
}