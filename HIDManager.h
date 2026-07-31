//=============================================================================
// File: HIDManager.h
// Commit: 4 (2/4)
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

    bool connected = false;
};

#endif//=============================================================================
// File: HIDManager.h
// Commit: 4
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
    bool connected = false;
};

#endif
