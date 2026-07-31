//=============================================================================
// File: App.cpp
// Commit: 3
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

    Storage.begin();
    Storage.load();

    Profile.begin();

    EventQueue.begin();

    Encoder.begin();
    Button.begin();

    Action.begin();

    Hid.begin();
}

void App::update()
{
    Encoder.update();
    Button.update();

    Action.update();

    Hid.update();
}
