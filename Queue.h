//=============================================================================
// File: Queue.h
// Commit: 7
//=============================================================================

#ifndef QUEUE_H
#define QUEUE_H

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

private:
    Event buffer[Capacity];

    volatile uint8_t head;
    volatile uint8_t tail;
    volatile uint8_t count;
};

extern Queue EventQueue;

#endif