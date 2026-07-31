//=============================================================================
// File: ButtonManager.h
// Commit: 2
//=============================================================================

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

class ButtonManager
{
public:
    void begin();
    void update();

private:
    bool lastState = true;
};

#endif
