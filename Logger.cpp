//=============================================================================
// File: Logger.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "Logger.h"
#include "Config.h"

Logger LoggerInstance;

void Logger::begin()
{
    Serial.begin(SERIAL_BAUDRATE);

    // Wait for a USB serial monitor to attach, but only for a couple of
    // seconds. This is a BLE controller, not something that should refuse
    // to start just because nobody opened a serial monitor - without this
    // timeout, the original blocking "while (!Serial)" would leave the
    // device stuck forever (never advertising over BLE) whenever it's
    // powered from a battery/USB charger instead of a PC.
    const uint32_t waitStart = millis();

    while (!Serial && (millis() - waitStart) < 2000)
    {
        delay(1);
    }
}

void Logger::info(const char* text)
{
    Serial.print("[INFO] ");
    Serial.println(text);
}

void Logger::warning(const char* text)
{
    Serial.print("[WARNING] ");
    Serial.println(text);
}

void Logger::error(const char* text)
{
    Serial.print("[ERROR] ");
    Serial.println(text);
}
