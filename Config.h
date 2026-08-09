//=============================================================================
// File: Config.h
// Commit: 11
// Version: 0.3.0
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
// Profiles
//=============================================================================

// One selectable profile per encoder (so a boot-time short-press on
// encoder N can select profile N - see BOOT_PROFILE_SELECT_WINDOW_MS
// below). Profile 0 is "OpenWebRX", defined in OpenWebRXProfile.cpp;
// profiles 1..N-1 start out empty (every button = no action) until you
// define them via the web config page.
constexpr uint8_t PROFILE_COUNT = ENCODER_COUNT;

// How long after boot the device watches for a short-press on any encoder
// to select that encoder's profile for this session. No press within this
// window -> profile 0 (OpenWebRX) loads, as before this feature existed.
constexpr uint32_t BOOT_PROFILE_SELECT_WINDOW_MS = 5000;

//=============================================================================
// WiFi Config Portal
//=============================================================================

// A small access point + web page ("http://192.168.4.1/" once connected)
// for defining what each encoder's 4 events send, per profile, and for
// switching the active profile - all without re-flashing the sketch.
//
// The AP name intentionally matches the BLE device name.
constexpr char AP_SSID[]     = "SDR Maestro";
constexpr char AP_PASSWORD[] = "aaaaaaaa"; // 8 chars = WPA2 minimum length

// The AP shuts itself off this long after boot, PROVIDED nobody is
// connected to it at that point - if a browser is still connected when the
// timer elapses, the AP stays up until that client disconnects, then shuts
// down. This limits how long the device is a joinable WiFi network without
// requiring you to remember to turn it off yourself.
constexpr uint32_t AP_TIMEOUT_MS = 5UL * 60UL * 1000UL; // 5 minutes

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
