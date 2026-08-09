//=============================================================================
// File: ActionCodec.cpp
// Commit: 11
// Version: 0.3.0
//=============================================================================

#include "ActionCodec.h"

#include <stdio.h>
#include <stdlib.h>

#include "BleHidKeyboard.h"

namespace
{
    struct NamedCode { const char* name; uint8_t code; };

    const NamedCode KEY_NAMES[] =
    {
        { "ENTER", HidKey::ENTER },
        { "ESC", HidKey::ESC },
        { "BACKSPACE", HidKey::BACKSPACE },
        { "TAB", HidKey::TAB },
        { "SPACE", HidKey::SPACE },
        { "MINUS", HidKey::MINUS },
        { "EQUAL", HidKey::EQUAL },
        { "F1", HidKey::F1 }, { "F2", HidKey::F2 }, { "F3", HidKey::F3 },
        { "F4", HidKey::F4 }, { "F5", HidKey::F5 }, { "F6", HidKey::F6 },
        { "F7", HidKey::F7 }, { "F8", HidKey::F8 }, { "F9", HidKey::F9 },
        { "F10", HidKey::F10 }, { "F11", HidKey::F11 }, { "F12", HidKey::F12 },
        { "INSERT", HidKey::INSERT },
        { "HOME", HidKey::HOME },
        { "PAGE_UP", HidKey::PAGE_UP },
        { "DELETE", HidKey::DELETE_FWD },
        { "END", HidKey::END },
        { "PAGE_DOWN", HidKey::PAGE_DOWN },
        { "RIGHT_ARROW", HidKey::RIGHT_ARROW },
        { "LEFT_ARROW", HidKey::LEFT_ARROW },
        { "DOWN_ARROW", HidKey::DOWN_ARROW },
        { "UP_ARROW", HidKey::UP_ARROW },
    };
    constexpr size_t KEY_NAMES_COUNT = sizeof(KEY_NAMES) / sizeof(KEY_NAMES[0]);

    const NamedCode MEDIA_NAMES[] =
    {
        { "PLAY_PAUSE", HidMediaKey::PLAY_PAUSE },
        { "NEXT_TRACK", HidMediaKey::NEXT_TRACK },
        { "PREV_TRACK", HidMediaKey::PREV_TRACK },
        { "MUTE", HidMediaKey::MUTE },
        { "VOLUME_UP", HidMediaKey::VOLUME_UP },
        { "VOLUME_DOWN", HidMediaKey::VOLUME_DOWN },
    };
    constexpr size_t MEDIA_NAMES_COUNT = sizeof(MEDIA_NAMES) / sizeof(MEDIA_NAMES[0]);

    const NamedCode MODIFIER_NAMES[] =
    {
        { "SHIFT", HidKey::LEFT_SHIFT },
        { "CTRL", HidKey::LEFT_CTRL },
        { "ALT", HidKey::LEFT_ALT },
        { "GUI", HidKey::LEFT_GUI },
        { "RSHIFT", HidKey::RIGHT_SHIFT },
        { "RCTRL", HidKey::RIGHT_CTRL },
        { "RALT", HidKey::RIGHT_ALT },
        { "RGUI", HidKey::RIGHT_GUI },
    };
    constexpr size_t MODIFIER_NAMES_COUNT = sizeof(MODIFIER_NAMES) / sizeof(MODIFIER_NAMES[0]);

    String upperCopy(String s)
    {
        s.trim();
        s.toUpperCase();
        return s;
    }

    bool lookupByName(const NamedCode* table, size_t count, const String& upperName, uint8_t& code)
    {
        for (size_t i = 0; i < count; i++)
        {
            if (upperName.equals(table[i].name))
            {
                code = table[i].code;
                return true;
            }
        }
        return false;
    }

    const char* nameForCode(const NamedCode* table, size_t count, uint8_t code)
    {
        for (size_t i = 0; i < count; i++)
        {
            if (table[i].code == code)
            {
                return table[i].name;
            }
        }
        return nullptr;
    }

    // Accepts "0x1B" style hex or a bare decimal number.
    bool parseNumber(const String& text, uint8_t& value)
    {
        if (text.length() == 0)
        {
            return false;
        }

        char* endPtr = nullptr;
        const long parsed = strtol(text.c_str(), &endPtr, 0); // base 0 = auto-detect 0x

        if (endPtr == text.c_str() || *endPtr != '\0')
        {
            return false;
        }

        if (parsed < 0 || parsed > 255)
        {
            return false;
        }

        value = static_cast<uint8_t>(parsed);
        return true;
    }

    String codeToText(const NamedCode* table, size_t count, uint8_t code)
    {
        const char* name = nameForCode(table, count, code);

        if (name != nullptr)
        {
            return String(name);
        }

        char hex[6];
        snprintf(hex, sizeof(hex), "0x%02X", code);
        return String(hex);
    }
}

KeyAction ActionCodec::parse(const String& rawText)
{
    KeyAction action; // defaults to KeyType::None

    String text = rawText;
    text.trim();

    if (text.length() == 0)
    {
        return action;
    }

    if (upperCopy(text) == "NONE")
    {
        return action;
    }

    const int colon = text.indexOf(':');

    if (colon < 0)
    {
        return action; // unrecognized form -> treat like "none"
    }

    const String prefix = upperCopy(text.substring(0, static_cast<unsigned int>(colon)));
    String rest = text.substring(static_cast<unsigned int>(colon) + 1);
    rest.trim();

    if (prefix == "CHAR")
    {
        if (rest.length() >= 1)
        {
            return HidKey::fromChar(rest[0]);
        }
        return action;
    }

    if (prefix == "KEY")
    {
        uint8_t modifier = 0;
        String keyToken;
        bool first = true;
        int start = 0;

        while (start <= static_cast<int>(rest.length()))
        {
            const int plus = rest.indexOf('+', start);
            String token = (plus < 0)
                ? rest.substring(static_cast<unsigned int>(start))
                : rest.substring(static_cast<unsigned int>(start), static_cast<unsigned int>(plus));
            token.trim();

            if (first)
            {
                keyToken = token;
                first = false;
            }
            else
            {
                uint8_t bit = 0;
                if (lookupByName(MODIFIER_NAMES, MODIFIER_NAMES_COUNT, upperCopy(token), bit))
                {
                    modifier |= bit;
                }
            }

            if (plus < 0)
            {
                break;
            }
            start = plus + 1;
        }

        uint8_t code = 0;

        if (lookupByName(KEY_NAMES, KEY_NAMES_COUNT, upperCopy(keyToken), code) || parseNumber(keyToken, code))
        {
            action.type = KeyType::Key;
            action.key = code;
            action.modifier = modifier;
        }

        return action;
    }

    if (prefix == "MEDIA")
    {
        uint8_t code = 0;

        if (lookupByName(MEDIA_NAMES, MEDIA_NAMES_COUNT, upperCopy(rest), code) || parseNumber(rest, code))
        {
            action.type = KeyType::MediaKey;
            action.key = code;
        }

        return action;
    }

    return action; // unrecognized prefix -> "none"
}

String ActionCodec::toString(const KeyAction& action)
{
    if (action.type == KeyType::Key)
    {
        String out = "KEY:";
        out += codeToText(KEY_NAMES, KEY_NAMES_COUNT, action.key);

        for (size_t i = 0; i < MODIFIER_NAMES_COUNT; i++)
        {
            if (action.modifier & MODIFIER_NAMES[i].code)
            {
                out += "+";
                out += MODIFIER_NAMES[i].name;
            }
        }

        return out;
    }

    if (action.type == KeyType::MediaKey)
    {
        String out = "MEDIA:";
        out += codeToText(MEDIA_NAMES, MEDIA_NAMES_COUNT, action.key);
        return out;
    }

    return "NONE";
}
