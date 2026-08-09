//=============================================================================
// File: SDR_Maestro.ino
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// Target: ESP32-S3 N16R8, Arduino IDE 2.x, ESP32 Core 3.3.11
//
// Uses only the BLE library bundled with the ESP32 Arduino core - no
// external "ESP32 BLE Keyboard" library needed. See BleHidKeyboard.h for
// details, and OpenWebRXProfile.cpp to define what each encoder does.
//=============================================================================

#include <Arduino.h>

#include "App.h"

App app;

void setup()
{
    app.begin();
}

void loop()
{
    app.update();
}
