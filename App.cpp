//=============================================================================
// File: App.cpp
// Commit: 6
//=============================================================================

#include "App.h"

#include "Logger.h"
#include "EncoderManager.h"
#include "ButtonManager.h"
#include "ActionManager.h"
#include "HIDManager.h"
#include "ProfileManager.h"
#include "StorageManager.h"
#include "Queue.h"

extern Logger LoggerInstance;
extern Queue EventQueue;

static EncoderManager Encoder;
static ButtonManager Button;
static ActionManager Action;
static HIDManager Hid;
static ProfileManager Profile;
static StorageManager Storage;

void App::begin()
{
    LoggerInstance.begin();

    LoggerInstance.info("========================================");
    LoggerInstance.info("SDR Maestro");
    LoggerInstance.info("Commit #6");
    LoggerInstance.info("Hardware configuration loaded.");
    LoggerInstance.info("========================================");

    Storage.begin();
    Storage.load();

    Profile.begin();

    EventQueue.begin();

    Hid.begin();

    Action.begin();
    Action.attachHID(&Hid);

    Encoder.begin();
    Button.begin();
}

void App::update()
{
    Hid.update();

    Encoder.update();
    Button.update();

    Action.update();
}