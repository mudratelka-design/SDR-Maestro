//=============================================================================
// File: HIDManager.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include <Arduino.h>

#include "Types.h"
#include "BleHidKeyboard.h"

class HIDManager
{
public:
    void begin();
    void update();

    bool isConnected() const;

    void execute(const KeyAction& action);

private:
    BleHidKeyboard hid;
};

extern HIDManager HIDManagerInstance;

#endif
