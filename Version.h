//=============================================================================
// File: Version.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef VERSION_H
#define VERSION_H

#define PROJECT_NAME        "SDR Maestro"
#define PROJECT_VERSION     "0.2.0"
#define PROJECT_COMMIT      "Commit 9"

// Commit 9 changes vs. the "fixed" skeleton this was based on:
//  - Removed the dependency on the external "ESP32 BLE Keyboard" library
//    (unmaintained, doesn't compile on ESP32 core 3.x). BLE HID keyboard +
//    media-key support is now implemented directly on top of the BLE
//    classes bundled with ESP32 Arduino core 3.x itself - see
//    BleHidKeyboard.h/.cpp. Nothing extra to install.
//  - Reworked the action/profile pipeline: each of the 5 encoders x 4
//    events (turnRight, turnLeft, short press, long press) now maps
//    directly to a KeyAction (a HID key or media key) via
//    OpenWebRXProfile.cpp, instead of going through an intermediate
//    "ActionType" enum that only had a few cases wired up in HIDManager.
//  - Fixed ButtonManager double-firing both the short-press AND the
//    long-press action on every long hold.
//  - Reworked EncoderManager to decode both quadrature pins with a
//    transition table (rejects bounce, counts full detents) instead of
//    only watching pin A.
//  - Logger no longer blocks forever in setup() waiting for a USB serial
//    monitor that may never attach.

#define PROJECT_BUILD_DATE  __DATE__
#define PROJECT_BUILD_TIME  __TIME__

#endif
