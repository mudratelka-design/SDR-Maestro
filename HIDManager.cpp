//=============================================================================
// File: HIDManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "HIDManager.h"

HIDManager HIDManagerInstance;

void HIDManager::begin()
{
    hid.begin("SDR Maestro", "mudratelka-design", 100);
}

void HIDManager::update()
{
    // Connection state is updated directly by BLE server callbacks inside
    // BleHidKeyboard; nothing to poll here. Kept for interface symmetry.
}

bool HIDManager::isConnected() const
{
    return hid.isConnected();
}

void HIDManager::execute(const KeyAction& action)
{
    switch (action.type)
    {
        case KeyType::Key:
            hid.sendKey(action.key, action.modifier);
            break;

        case KeyType::MediaKey:
            hid.sendMediaKey(action.key);
            break;

        case KeyType::None:
        default:
            break;
    }
}
