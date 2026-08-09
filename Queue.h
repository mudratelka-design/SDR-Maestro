//=============================================================================
// File: Queue.h
// Commit: 9
// Version: 0.2.0
//=============================================================================

#ifndef SDR_MAESTRO_QUEUE_H
#define SDR_MAESTRO_QUEUE_H

#include <Arduino.h>
#include "Events.h"

class Queue
{
public:
    static constexpr uint8_t Capacity = 32;

    void begin();

    bool push(const Event& event);
    bool pop(Event& event);

    bool isEmpty() const;
    bool isFull() const;
    uint8_t size() const;

private:
    Event buffer[Capacity];

    uint8_t head;
    uint8_t tail;
    uint8_t count;
};

extern Queue EventQueue;

#endif
