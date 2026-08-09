//=============================================================================
// File: BleHidKeyboard.h
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// Minimal, self-contained BLE HID keyboard + consumer-control (media key)
// transmitter for ESP32-S3.
//
// WHY NOT THE "ESP32 BLE Keyboard" LIBRARY?
// ----------------------------------------------------------------------
// The commonly used T-vK/ESP32-BLE-Keyboard library hasn't been updated
// since 2021 and does not compile against ESP32 Arduino core 3.x: the
// core's own BLE API changed underneath it (BLEDevice::init() and
// BLECharacteristic::setValue() now take an Arduino String instead of a
// std::string, etc.), and even its "NimBLE mode" now collides with class
// names the core itself uses internally. This is, by far, the most
// commonly reported compile failure for this kind of project.
//
// The fix used here is to not depend on any external BLE-keyboard library
// at all. ESP32 Arduino core 3.x already ships its own BLE stack
// (BLEDevice / BLEServer / BLEHIDDevice / BLECharacteristic) as part of
// the board package you already have installed - nothing extra to add,
// nothing that can silently go out of sync with your core version. This
// file is the small amount of HID glue code sitting on top of that.
//=============================================================================

#ifndef BLE_HID_KEYBOARD_H
#define BLE_HID_KEYBOARD_H

#include <Arduino.h>

#include "Types.h"

class BLECharacteristic; // defined in the ESP32 core's bundled BLE library

// Standard USB HID keyboard usage codes (Usage Page 0x07) - the subset used
// by this project. Add more as needed; see the USB HID Usage Tables,
// "Keyboard/Keypad Page (0x07)", for the full list.
namespace HidKey
{
    // Modifier bits (OR together, pass as KeyAction::modifier)
    constexpr uint8_t LEFT_CTRL   = 0x01;
    constexpr uint8_t LEFT_SHIFT  = 0x02;
    constexpr uint8_t LEFT_ALT    = 0x04;
    constexpr uint8_t LEFT_GUI    = 0x08;
    constexpr uint8_t RIGHT_CTRL  = 0x10;
    constexpr uint8_t RIGHT_SHIFT = 0x20;
    constexpr uint8_t RIGHT_ALT   = 0x40;
    constexpr uint8_t RIGHT_GUI   = 0x80;

    // Common keys
    constexpr uint8_t ENTER      = 0x28;
    constexpr uint8_t ESC        = 0x29;
    constexpr uint8_t BACKSPACE  = 0x2A;
    constexpr uint8_t TAB        = 0x2B;
    constexpr uint8_t SPACE      = 0x2C;
    constexpr uint8_t MINUS      = 0x2D;
    constexpr uint8_t EQUAL      = 0x2E;

    constexpr uint8_t F1  = 0x3A;
    constexpr uint8_t F2  = 0x3B;
    constexpr uint8_t F3  = 0x3C;
    constexpr uint8_t F4  = 0x3D;
    constexpr uint8_t F5  = 0x3E;
    constexpr uint8_t F6  = 0x3F;
    constexpr uint8_t F7  = 0x40;
    constexpr uint8_t F8  = 0x41;
    constexpr uint8_t F9  = 0x42;
    constexpr uint8_t F10 = 0x43;
    constexpr uint8_t F11 = 0x44;
    constexpr uint8_t F12 = 0x45;

    constexpr uint8_t INSERT     = 0x49;
    constexpr uint8_t HOME       = 0x4A;
    constexpr uint8_t PAGE_UP    = 0x4B;
    constexpr uint8_t DELETE_FWD = 0x4C;
    constexpr uint8_t END        = 0x4D;
    constexpr uint8_t PAGE_DOWN  = 0x4E;

    constexpr uint8_t RIGHT_ARROW = 0x4F;
    constexpr uint8_t LEFT_ARROW  = 0x50;
    constexpr uint8_t DOWN_ARROW  = 0x51;
    constexpr uint8_t UP_ARROW    = 0x52;

    // Converts a printable ASCII character ('a'-'z', 'A'-'Z', '0'-'9', ' ')
    // into a KeyAction. Unsupported characters come back as KeyType::None -
    // add more cases in BleHidKeyboard.cpp if you need punctuation this
    // project doesn't use yet.
    KeyAction fromChar(char c);
}

// Consumer-control (media key) usage codes (Usage Page 0x0C) - the subset
// used by this project.
namespace HidMediaKey
{
    constexpr uint8_t PLAY_PAUSE  = 0xCD;
    constexpr uint8_t NEXT_TRACK  = 0xB5;
    constexpr uint8_t PREV_TRACK  = 0xB6;
    constexpr uint8_t MUTE        = 0xE2;
    constexpr uint8_t VOLUME_UP   = 0xE9;
    constexpr uint8_t VOLUME_DOWN = 0xEA;
}

class BleHidKeyboard
{
public:
    void begin(const char* deviceName, const char* manufacturer, uint8_t batteryLevel = 100);

    bool isConnected() const;

    // Sends a regular keyboard key with an optional modifier mask
    // (HidKey::* bits OR'd together) as a quick press-then-release.
    void sendKey(uint8_t keyCode, uint8_t modifier = 0);

    // Sends a consumer-control / media key as a quick press-then-release.
    void sendMediaKey(uint8_t usageCode);

    // Called by the internal BLE server callbacks - not for outside use.
    void setConnected(bool state);

private:
    BLECharacteristic* keyboardReport = nullptr;
    BLECharacteristic* mediaReport = nullptr;

    volatile bool connected = false;
};

#endif
