//=============================================================================
// File: StorageManager.h
// Commit: 11
// Version: 0.3.0
//=============================================================================

#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <Arduino.h>
#include <Preferences.h>

#include "Config.h"
#include "Types.h"

// Persists per-profile button bindings to flash (NVS) via the Preferences
// library, bundled with the ESP32 Arduino core - no external dependency.
// Bindings are written only when saved from the web config page; anything
// never saved simply isn't found on load, and the caller's existing value
// (normally KeyType::None, or an OpenWebRXProfile default for profile 0)
// is left alone.
class StorageManager
{
public:
    void begin();

    // Fills clockwise[]/counterClockwise[]/shortPress[]/longPress[] (each
    // ENCODER_COUNT long) with whatever was saved for this profile.
    void loadProfile(
        uint8_t profile,
        KeyAction clockwise[],
        KeyAction counterClockwise[],
        KeyAction shortPress[],
        KeyAction longPress[]);

    void saveProfile(
        uint8_t profile,
        const KeyAction clockwise[],
        const KeyAction counterClockwise[],
        const KeyAction shortPress[],
        const KeyAction longPress[]);

private:
    Preferences preferences;

    void loadAction(const char* key, KeyAction& action);
    void saveAction(const char* key, const KeyAction& action);
};

extern StorageManager StorageManagerInstance;

#endif
