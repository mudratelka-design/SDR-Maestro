//=============================================================================
// File: SDR_Maestro.ino
// Commit: 1
//=============================================================================

#include "Config.h"
#include "Version.h"
#include "Logger.h"

Logger LoggerInstance;

void setup()
{
    LoggerInstance.begin();

    LoggerInstance.info(PROJECT_NAME);
    LoggerInstance.info(PROJECT_VERSION);
}

void loop()
{
}
