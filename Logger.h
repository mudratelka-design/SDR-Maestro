//=============================================================================
// File: Logger.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:
    void begin();

    void info(const char* text);
    void warning(const char* text);
    void error(const char* text);
};

extern Logger LoggerInstance;

#endif
