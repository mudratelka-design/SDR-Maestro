//=============================================================================
// File: StorageManager.cpp
// Commit: 11
// Version: 0.3.0
//=============================================================================
//
// Each (profile, encoder, event) binding is stored under its own short NVS
// key - Preferences keys are limited to 15 characters, so the scheme below
// packs profile/event/encoder into a handful of characters, e.g. "p0c3" =
// profile 0, clockwise, encoder 3.
//=============================================================================

#include "StorageManager.h"

#include <stdio.h>

namespace
{
    // eventLetter: 'c' = clockwise, 'w' = counter-clockwise, 's' = short
    // press, 'l' = long press.
    void makeKey(char* out, size_t outSize, uint8_t profile, char eventLetter, uint8_t encoder)
    {
        snprintf(out, outSize, "p%u%c%u", profile, eventLetter, encoder);
    }
}

StorageManager StorageManagerInstance;

void StorageManager::begin()
{
    preferences.begin("sdrmaestro", false);
}

void StorageManager::loadAction(const char* key, KeyAction& action)
{
    uint8_t buf[3] = { 0, 0, 0 };
    const size_t got = preferences.getBytes(key, buf, sizeof(buf));

    if (got == sizeof(buf))
    {
        action.type = static_cast<KeyType>(buf[0]);
        action.key = buf[1];
        action.modifier = buf[2];
    }
    // else: nothing saved yet for this slot - leave the caller's existing
    // (pre-filled) value alone.
}

void StorageManager::saveAction(const char* key, const KeyAction& action)
{
    const uint8_t buf[3] =
    {
        static_cast<uint8_t>(action.type),
        action.key,
        action.modifier
    };

    preferences.putBytes(key, buf, sizeof(buf));
}

void StorageManager::loadProfile(
    uint8_t profile,
    KeyAction clockwise[],
    KeyAction counterClockwise[],
    KeyAction shortPress[],
    KeyAction longPress[])
{
    char key[8];

    for (uint8_t e = 0; e < ENCODER_COUNT; e++)
    {
        makeKey(key, sizeof(key), profile, 'c', e); loadAction(key, clockwise[e]);
        makeKey(key, sizeof(key), profile, 'w', e); loadAction(key, counterClockwise[e]);
        makeKey(key, sizeof(key), profile, 's', e); loadAction(key, shortPress[e]);
        makeKey(key, sizeof(key), profile, 'l', e); loadAction(key, longPress[e]);
    }
}

void StorageManager::saveProfile(
    uint8_t profile,
    const KeyAction clockwise[],
    const KeyAction counterClockwise[],
    const KeyAction shortPress[],
    const KeyAction longPress[])
{
    char key[8];

    for (uint8_t e = 0; e < ENCODER_COUNT; e++)
    {
        makeKey(key, sizeof(key), profile, 'c', e); saveAction(key, clockwise[e]);
        makeKey(key, sizeof(key), profile, 'w', e); saveAction(key, counterClockwise[e]);
        makeKey(key, sizeof(key), profile, 's', e); saveAction(key, shortPress[e]);
        makeKey(key, sizeof(key), profile, 'l', e); saveAction(key, longPress[e]);
    }
}
