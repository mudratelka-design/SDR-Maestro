//=============================================================================
// File: SDR_Maestro.ino
// Commit: 11
// Version: 0.3.0
//=============================================================================
//
// Target: ESP32-S3 N16R8, Arduino IDE 2.x, ESP32 Core 3.3.11
//
// Uses only libraries bundled with the ESP32 Arduino core (BLE, WiFi,
// WebServer, Preferences) - no external libraries to install. In
// particular, no "ESP32 BLE Keyboard" library: that one hasn't been
// updated since 2021 and doesn't compile against core 3.x. See
// BleHidKeyboard.h for details.
//
// Key bindings, per profile: OpenWebRXProfile.cpp defines profile 0's
// defaults; edit any profile at runtime from the web config page (connect
// to WiFi "SDR Maestro" for the first few minutes after boot - see
// Config.h for the SSID/password). See WebConfigServer.h and
// ActionCodec.h for how that page works.
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
