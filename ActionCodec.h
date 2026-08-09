//=============================================================================
// File: ActionCodec.h
// Commit: 11
// Version: 0.3.0
//=============================================================================

#ifndef ACTION_CODEC_H
#define ACTION_CODEC_H

#include <Arduino.h>

#include "Types.h"

// Converts between a KeyAction and the small human-readable text format
// used in each box of the web config page:
//
//   NONE
//   KEY:UP_ARROW
//   KEY:TAB+SHIFT
//   KEY:0x29
//   CHAR:m
//   MEDIA:VOLUME_UP
//   MEDIA:0xE9
//
// See ActionCodec.cpp for the full list of recognized KEY:/MEDIA: names.
// Anything unrecognized parses as KeyType::None (same as leaving a box
// blank), so a typo never crashes the page - it just does nothing until
// corrected.
namespace ActionCodec
{
    KeyAction parse(const String& text);
    String toString(const KeyAction& action);
}

#endif
