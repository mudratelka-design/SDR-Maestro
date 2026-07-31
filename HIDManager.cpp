//=============================================================================
// File: HIDManager.cpp
// Commit: 4
//=============================================================================

#include "HIDManager.h"

#include <BleKeyboard.h>

static BleKeyboard BleHID(
    "SDR Maestro",
    "OpenAI",
    100);

void HIDManager::begin()
{
    BleHID.begin();
}

void HIDManager::update()
{
    connected = BleHID.isConnected();
}

bool HIDManager::isConnected() const
{
    return connected;
}

void HIDManager::execute(const Action& action)
{
    (void)action;

    // Commit #4 (2/4)
    // Mouse support.

    // Commit #4 (3/4)
    // Keyboard support.

    // Commit #4 (4/4)
    // Consumer keys support.
}
