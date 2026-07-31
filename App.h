//=============================================================================
// File: App.h
// Commit: 7
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
    EncoderManager Encoder;
    ButtonManager Button;
};

#endif