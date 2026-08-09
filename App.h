//=============================================================================
// File: App.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef APP_H
#define APP_H

#include "EncoderManager.h"
#include "ButtonManager.h"

class App
{
public:
    void begin();
    void update();

private:
    EncoderManager encoderManager;
    ButtonManager buttonManager;
};

#endif
