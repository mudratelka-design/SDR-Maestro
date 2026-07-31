//=============================================================================
// File: SDR_Maestro.ino
// Commit: 6
//=============================================================================

#include <Arduino.h>

#include "App.h"

static App app;

void setup()
{
    app.begin();
}

void loop()
{
    app.update();
}
