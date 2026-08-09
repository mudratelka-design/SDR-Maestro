//=============================================================================
// File: Config.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//=============================================================================
// Serial
//=============================================================================

constexpr uint32_t SERIAL_BAUDRATE = 115200;

//=============================================================================
// Hardware
//=============================================================================

constexpr uint8_t ENCODER_COUNT = 5;

// How many quadrature transitions make up one physical detent click.
// Most cheap mechanical rotary encoders (e.g. EC11 / KY-040 modules) output
// 4 transitions per detent. If turning one "click" fires two or more events,
// try 2 instead. If it fires nothing, try 1.
constexpr int8_t ENCODER_STEPS_PER_DETENT = 4;

//=============================================================================
// Buttons
//=============================================================================

constexpr uint16_t BUTTON_DEBOUNCE_MS   = 30;
constexpr uint16_t BUTTON_LONG_PRESS_MS = 800;

//=============================================================================
// Encoder Pins
//=============================================================================

struct EncoderPins
{
    uint8_t pinA;
    uint8_t pinB;
    uint8_t pinButton;
};

// GPIO4-GPIO18 are safe, freely usable pins on the ESP32-S3 N16R8 module:
// they don't collide with the strapping pins (0, 3, 45, 46), the native
// USB pins (19, 20), or the octal SPI flash/PSRAM pins (26-32, 33-37 on
// N16R8 boards that use octal PSRAM). Re-check this table if you move to a
// different ESP32-S3 board/module.
constexpr EncoderPins ENCODERS[ENCODER_COUNT] =
{
    {  4,  5, 14 },   // Encoder #1
    {  6,  7, 15 },   // Encoder #2
    {  8,  9, 16 },   // Encoder #3
    { 10, 11, 17 },   // Encoder #4
    { 12, 13, 18 }    // Encoder #5
};

//=============================================================================
// Hardware Notes
//=============================================================================
//
// Rotary encoder modules contain onboard pull-up resistors.
//
// GPIO configuration:
//
//     pinMode(pin, INPUT);
//
// If another encoder without onboard pull-ups is used:
//
//     pinMode(pin, INPUT_PULLUP);
//
//=============================================================================

#endif
