//=============================================================================
// File: App.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "App.h"

#include "Version.h"
#include "Logger.h"

#include "Queue.h"

#include "ProfileManager.h"
#include "StorageManager.h"

#include "HIDManager.h"
#include "ActionManager.h"

void App::begin()
{
    LoggerInstance.begin();

    LoggerInstance.info("========================================");
    LoggerInstance.info(PROJECT_NAME);
    LoggerInstance.info(PROJECT_VERSION);
    LoggerInstance.info(PROJECT_COMMIT);
    LoggerInstance.info("========================================");

    EventQueue.begin();

    StorageManagerInstance.begin();
    StorageManagerInstance.load();

    ProfileManagerInstance.begin();

    HIDManagerInstance.begin();

    ActionManagerInstance.begin();
    ActionManagerInstance.attachHID(&HIDManagerInstance);

    encoderManager.begin();
    buttonManager.begin();

    LoggerInstance.info("Initialization complete. Advertising over BLE as \"SDR Maestro\".");
}

void App::update()
{
    HIDManagerInstance.update();

    encoderManager.update();
    buttonManager.update();

    ActionManagerInstance.update();
}
