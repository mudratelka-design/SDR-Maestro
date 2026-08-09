//=============================================================================
// File: OpenWebRXProfile.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// Key bindings for all 5 encoders x 4 events (turnRight, turnLeft, short
// press, long press) live here, and only here. Encoders #1-#3 below are
// filled in with a working example so you can verify BLE connectivity end
// to end; #4 and #5 are intentionally left unbound (KeyType::None, i.e. no
// action) - copy the pattern shown to define them once you've decided on
// your own layout, per the note in your original request.
//
// Helpers available:
//   key(HidKey::SOME_KEY, [modifier])  -> a specific HID keycode
//   charKey('a')                       -> a letter/digit typed as-is
//   media(HidMediaKey::SOME_KEY)       -> a consumer-control / media key
//   none()                             -> no action (the default)
//=============================================================================

#include "OpenWebRXProfile.h"

#include "BleHidKeyboard.h"

namespace
{
    KeyAction key(uint8_t code, uint8_t modifier = 0)
    {
        KeyAction action;
        action.type = KeyType::Key;
        action.key = code;
        action.modifier = modifier;
        return action;
    }

    KeyAction charKey(char c)
    {
        return HidKey::fromChar(c);
    }

    KeyAction media(uint8_t code)
    {
        KeyAction action;
        action.type = KeyType::MediaKey;
        action.key = code;
        return action;
    }

    KeyAction none()
    {
        return KeyAction{};
    }
}

void OpenWebRXProfile::load(
    KeyAction clockwise[],
    KeyAction counterClockwise[],
    KeyAction shortPress[],
    KeyAction longPress[])
{
    for (uint8_t i = 0; i < ENCODER_COUNT; i++)
    {
        clockwise[i] = none();
        counterClockwise[i] = none();
        shortPress[i] = none();
        longPress[i] = none();
    }

    // -----------------------------------------------------------------
    // Encoder #1 - Frequency tuning (working example)
    //   turnRight / turnLeft -> Up / Down arrow
    //   short press          -> "m" (mute, if bound in your OpenWebRX)
    // -----------------------------------------------------------------
    clockwise[0]        = key(HidKey::UP_ARROW);
    counterClockwise[0] = key(HidKey::DOWN_ARROW);
    shortPress[0]       = charKey('m');

    // -----------------------------------------------------------------
    // Encoder #2 - Volume (working example)
    //   turnRight / turnLeft -> Volume Up / Down (BLE media keys)
    //   short press          -> Mute
    // -----------------------------------------------------------------
    clockwise[1]        = media(HidMediaKey::VOLUME_UP);
    counterClockwise[1] = media(HidMediaKey::VOLUME_DOWN);
    shortPress[1]       = media(HidMediaKey::MUTE);

    // -----------------------------------------------------------------
    // Encoder #3 - Mode switching (working example)
    //   turnRight / turnLeft -> Tab / Shift+Tab
    // -----------------------------------------------------------------
    clockwise[2]        = key(HidKey::TAB);
    counterClockwise[2] = key(HidKey::TAB, HidKey::LEFT_SHIFT);

    // -----------------------------------------------------------------
    // Encoder #4 and #5 - left for you to define. Example:
    //   clockwise[3]        = charKey('x');
    //   counterClockwise[3] = charKey('y');
    //   shortPress[3]       = media(HidMediaKey::PLAY_PAUSE);
    //   longPress[3]        = key(HidKey::ESC);
    // -----------------------------------------------------------------
}
