//=============================================================================
// File: Types.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

// Reserved for future use (e.g. UI/status reporting). Not currently used by
// any manager - ButtonManager tracks press state internally.
enum class ButtonState : uint8_t
{
    Released = 0,
    Pressed,
    LongPressed
};

enum class KeyType : uint8_t
{
    None = 0,
    Key,       // Regular keyboard key (HID keycode), optional modifier byte
    MediaKey   // Consumer-control / media key (volume, mute, play/pause, ...)
};

// What a single encoder event (turnLeft / turnRight / short press / long
// press) should send over BLE. A whole profile is just 5 x 4 of these -
// see OpenWebRXProfile.cpp to (re)define every button in one place.
struct KeyAction
{
    KeyType type = KeyType::None;
    uint8_t key = 0;
    uint8_t modifier = 0; // OR of HidKey::LEFT_SHIFT etc. (0 = none)
};

#endif
