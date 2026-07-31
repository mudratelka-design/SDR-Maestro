//=============================================================================
// File: Queue.h
// Commit: 2
//=============================================================================

#ifndef QUEUE_H
#define QUEUE_H

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

    volatile uint8_t head = 0;
    volatile uint8_t tail = 0;
    volatile uint8_t count = 0;
};

extern Queue EventQueue;

#endif
