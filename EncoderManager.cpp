//=============================================================================
// File: EncoderManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// Reads both quadrature pins (not just A) and only emits a turn event once
// a full detent's worth of valid transitions has accumulated. This is more
// reliable than watching pin A alone: it rejects contact bounce / invalid
// transitions instead of turning them into phantom extra steps, and it
// won't drop a step just because loop() happened to run a little late.
//
// If a knob feels reversed (turnRight fires turnLeft's action), swap pinA
// and pinB for that encoder in Config.h.
//=============================================================================

#include "EncoderManager.h"

#include "Events.h"
#include "Queue.h"

namespace
{
    // Index = (previous 2-bit AB state << 2) | (current 2-bit AB state).
    // Value = +1 for a valid clockwise step, -1 for counter-clockwise,
    //          0 for a repeated/invalid/bounced transition (ignored).
    const int8_t QUADRATURE_TABLE[16] =
    {
         0, -1,  1,  0,
         1,  0,  0, -1,
        -1,  0,  0,  1,
         0,  1, -1,  0
    };
}

void EncoderManager::begin()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        pinMode(ENCODERS[i].pinA, INPUT);
        pinMode(ENCODERS[i].pinB, INPUT);

        const uint8_t a = digitalRead(ENCODERS[i].pinA);
        const uint8_t b = digitalRead(ENCODERS[i].pinB);

        lastState[i] = static_cast<uint8_t>((a << 1) | b);
        accumulator[i] = 0;
    }
}

void EncoderManager::update()
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        const uint8_t a = digitalRead(ENCODERS[i].pinA);
        const uint8_t b = digitalRead(ENCODERS[i].pinB);
        const uint8_t state = static_cast<uint8_t>((a << 1) | b);

        if (state == lastState[i])
        {
            continue;
        }

        const uint8_t index = static_cast<uint8_t>((lastState[i] << 2) | state);
        accumulator[i] = static_cast<int8_t>(accumulator[i] + QUADRATURE_TABLE[index & 0x0F]);
        lastState[i] = state;

        if (accumulator[i] >= ENCODER_STEPS_PER_DETENT)
        {
            accumulator[i] = 0;

            Event event;
            event.encoder = i;
            event.type = EventType::EncoderClockwise;
            event.value = 1;

            EventQueue.push(event);
        }
        else if (accumulator[i] <= -ENCODER_STEPS_PER_DETENT)
        {
            accumulator[i] = 0;

            Event event;
            event.encoder = i;
            event.type = EventType::EncoderCounterClockwise;
            event.value = -1;

            EventQueue.push(event);
        }
    }
}
