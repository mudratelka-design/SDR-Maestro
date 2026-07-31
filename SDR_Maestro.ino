//=============================================================================
// File: SDR_Maestro.ino
// Commit: 5
//=============================================================================

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
