//=============================================================================
// File: Logger.cpp
// Commit: 7
//=============================================================================

#include "Logger.h"
#include "Config.h"

Logger LoggerInstance;

void Logger::begin()
{
    Serial.begin(SERIAL_BAUDRATE);

    while (!Serial)
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
    Serial.print("[WARN] ");
    Serial.println(text);
}

void Logger::error(const char* text)
{
    Serial.print("[ERROR] ");
    Serial.println(text);
}