//=============================================================================
// File: Config.h
// Commit: 6
//=============================================================================

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

static constexpr uint32_t SERIAL_BAUDRATE = 115200;

static constexpr uint8_t ENCODER_COUNT = 5;

static constexpr uint16_t BUTTON_DEBOUNCE_MS   = 30;
static constexpr uint16_t BUTTON_LONG_PRESS_MS = 800;

struct EncoderPins
{
    uint8_t pinA;
    uint8_t pinB;
    uint8_t pinKey;
};

static constexpr EncoderPins ENCODERS[ENCODER_COUNT] =
{
    {  4,  5, 14 },   // Encoder #1
    {  6,  7, 15 },   // Encoder #2
    {  8,  9, 16 },   // Encoder #3
    { 10, 11, 17 },   // Encoder #4
    { 12, 13, 18 }    // Encoder #5
};

/*
    Encoder modules contain onboard pull-up resistors.

    GPIO configuration:
        pinMode(pin, INPUT);

    If another encoder without pull-ups is used:
        pinMode(pin, INPUT_PULLUP);
*/

#endif
