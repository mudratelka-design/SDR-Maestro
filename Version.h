//=============================================================================
// File: Version.h
// Commit: 10
// Version: 0.2.1
//=============================================================================

#ifndef VERSION_H
#define VERSION_H

#define PROJECT_NAME        "SDR Maestro"
#define PROJECT_VERSION     "0.3.0"
#define PROJECT_COMMIT      "Commit 11"

// Commit 11 changes:
//  - Added a WiFi config portal: the device runs a small access point
//    (AP_SSID/AP_PASSWORD in Config.h) with a web page for defining what
//    each encoder's 4 events send, per profile, and for switching the
//    active profile - all without re-flashing the sketch. See
//    WebConfigServer.h/.cpp and ActionCodec.h/.cpp (the small text format
//    used in each field, e.g. "KEY:UP_ARROW", "MEDIA:VOLUME_UP").
//  - Added multi-profile support: ProfileManager now holds PROFILE_COUNT
//    (= ENCODER_COUNT) independent button layouts instead of one. Profile
//    0 is OpenWebRX (the existing compiled-in defaults); profiles 1+ start
//    empty until defined via the web page.
//  - Added boot-time profile selection: short-press any encoder within
//    BOOT_PROFILE_SELECT_WINDOW_MS (default 5s) of power-on to make that
//    encoder's numbered profile active for that session. No press ->
//    profile 0 (OpenWebRX), same behavior as before this feature existed.
//    See App::runBootProfileSelection().
//  - The config AP shuts itself off AP_TIMEOUT_MS (default 5 min) after
//    boot, provided nobody is connected to it at that point; if a browser
//    is still connected when the timer elapses, the AP stays up until
//    that client disconnects.
//  - StorageManager now actually persists (via the ESP32 core's bundled
//    Preferences/NVS library - no external dependency): each profile's
//    web-UI customizations are saved per (profile, encoder, event) and
//    reloaded on every boot, overlaid on top of the in-RAM defaults.
//
// Commit 10 changes:
//  - Fixed a boot-loop crash (Guru Meditation Error: LoadProhibited) in
//    BleHidKeyboard::begin(). The single-argument hid->manufacturer(name)
//    setter dereferences a BLEHIDDevice member that the ESP32 core's own
//    BLEHIDDevice constructor never initializes; only the no-argument
//    hid->manufacturer() getter actually creates that characteristic.
//    Fixed by calling the getter first: hid->manufacturer()->setValue(name).
//
// Commit 9 changes vs. the "fixed" skeleton this was based on:
//  - Removed the dependency on the external "ESP32 BLE Keyboard" library
//    (unmaintained, doesn't compile on ESP32 core 3.x). BLE HID keyboard +
//    media-key support is now implemented directly on top of the BLE
//    classes bundled with ESP32 Arduino core 3.x itself - see
//    BleHidKeyboard.h/.cpp. Nothing extra to install.
//  - Reworked the action/profile pipeline: each of the 5 encoders x 4
//    events (turnRight, turnLeft, short press, long press) now maps
//    directly to a KeyAction (a HID key or media key) via
//    OpenWebRXProfile.cpp, instead of going through an intermediate
//    "ActionType" enum that only had a few cases wired up in HIDManager.
//  - Fixed ButtonManager double-firing both the short-press AND the
//    long-press action on every long hold.
//  - Reworked EncoderManager to decode both quadrature pins with a
//    transition table (rejects bounce, counts full detents) instead of
//    only watching pin A.
//  - Logger no longer blocks forever in setup() waiting for a USB serial
//    monitor that may never attach.

#define PROJECT_BUILD_DATE  __DATE__
#define PROJECT_BUILD_TIME  __TIME__

#endif
