//=============================================================================
// File: HIDManager.h
// Commit: 4 (4/4)
//=============================================================================

#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include <Arduino.h>
#include "Types.h"

class HIDManager
{
public:
    void begin();
    void update();

    bool isConnected() const;

    void execute(const Action& action);

private:
    void executeMouse(const Action& action);
    void executeKeyboard(const Action& action);
    void executeConsumerKeys(const Action& action);

    bool connected = false;
};

#endif
