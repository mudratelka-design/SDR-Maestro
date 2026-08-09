//=============================================================================
// File: App.h
// Commit: 11
// Version: 0.3.0
//=============================================================================

#ifndef APP_H
#define APP_H

#include "EncoderManager.h"
#include "ButtonManager.h"
#include "WebConfigServer.h"

class App
{
public:
    void begin();
    void update();

private:
    EncoderManager encoderManager;
    ButtonManager buttonManager;

    // Blocks for up to BOOT_PROFILE_SELECT_WINDOW_MS right after boot,
    // watching for a short-press on any encoder to select that encoder's
    // profile for this session. No press -> profile 0 (OpenWebRX) stays
    // active, same as before this feature existed.
    void runBootProfileSelection();
};

#endif
