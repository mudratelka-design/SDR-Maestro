//=============================================================================
// File: App.cpp
// Commit: 11
// Version: 0.3.0
//=============================================================================

#include "App.h"

#include <stdio.h>

#include "Version.h"
#include "Logger.h"

#include "Queue.h"
#include "Events.h"

#include "ProfileManager.h"
#include "StorageManager.h"

#include "HIDManager.h"
#include "ActionManager.h"

#include "Config.h"

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

    // Loads every profile: profile 0 from OpenWebRXProfile's compiled-in
    // defaults, all profiles then overlaid with anything saved to flash
    // from the web config UI.
    ProfileManagerInstance.begin();

    HIDManagerInstance.begin();

    ActionManagerInstance.begin();
    ActionManagerInstance.attachHID(&HIDManagerInstance);

    encoderManager.begin();
    buttonManager.begin();

    runBootProfileSelection();

    WebConfigServerInstance.begin();

    LoggerInstance.info("Initialization complete. Advertising over BLE as \"SDR Maestro\".");
}

void App::update()
{
    HIDManagerInstance.update();

    encoderManager.update();
    buttonManager.update();

    ActionManagerInstance.update();

    WebConfigServerInstance.update();
}

void App::runBootProfileSelection()
{
    char msg[96];
    snprintf(msg, sizeof(msg),
              "Boot profile window open for %lu ms - short-press an encoder to pick its profile.",
              static_cast<unsigned long>(BOOT_PROFILE_SELECT_WINDOW_MS));
    LoggerInstance.info(msg);

    const uint32_t start = millis();
    bool selected = false;

    while (!selected && (millis() - start) < BOOT_PROFILE_SELECT_WINDOW_MS)
    {
        encoderManager.update();
        buttonManager.update();

        Event event;

        while (EventQueue.pop(event))
        {
            if (event.type == EventType::ButtonPressed && event.encoder < PROFILE_COUNT)
            {
                ProfileManagerInstance.setActiveProfile(event.encoder);
                selected = true;
                break;
            }
        }

        delay(1); // yield periodically so the task watchdog doesn't fire during this ~5s poll
    }

    // Discard anything else queued during the window (extra turns/presses)
    // so it isn't replayed as a real BLE key-press once the main loop starts.
    Event discard;
    while (EventQueue.pop(discard)) {}

    if (!selected)
    {
        LoggerInstance.info("Boot profile window closed - using default profile.");
    }
}
