//=============================================================================
// File: App.cpp
// Commit: 7
//=============================================================================

#include "App.h"

#include "Version.h"
#include "Logger.h"

#include "Queue.h"

#include "EncoderManager.h"
#include "ButtonManager.h"
#include "ActionManager.h"
#include "HIDManager.h"

#include "ProfileManager.h"
#include "StorageManager.h"

void App::begin()
{
    LoggerInstance.begin();

    LoggerInstance.info("========================================");
    LoggerInstance.info(PROJECT_NAME);
    LoggerInstance.info(PROJECT_VERSION);
    LoggerInstance.info(PROJECT_COMMIT);
    LoggerInstance.info("========================================");

    StorageManagerInstance.begin();
    StorageManagerInstance.load();

    ProfileManagerInstance.begin();

    EventQueue.begin();

    HIDManagerInstance.begin();

    ActionManagerInstance.begin();
    ActionManagerInstance.attachHID(&HIDManagerInstance);

    Encoder.begin();
    Button.begin();
}

void App::update()
{
    HIDManagerInstance.update();

    Encoder.update();
    Button.update();

    ActionManagerInstance.update();
}