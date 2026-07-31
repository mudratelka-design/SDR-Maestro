//=============================================================================
// File: SDR_Maestro.ino
// Commit: 7
//=============================================================================

#include <Arduino.h>

#include "App.h"

App Application;

void setup()
{
    Application.begin();
}

void loop()
{
    Application.update();
}