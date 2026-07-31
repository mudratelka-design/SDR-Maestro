//=============================================================================
// File: Queue.cpp
// Commit: 7
//=============================================================================

#include "Queue.h"

Queue EventQueue;

void Queue::begin()
{
    head = 0;
    tail = 0;
    count = 0;
}

bool Queue::push(const Event& event)
{
    if (isFull())
    {
        return false;
    }

    buffer[head] = event;

    head = (head + 1) % Capacity;

    count++;

    return true;
}

bool Queue::pop(Event& event)
{
    if (isEmpty())
    {
        return false;
    }

    event = buffer[tail];

    tail = (tail + 1) % Capacity;

    count--;

    return true;
}

bool Queue::isEmpty() const
{
    return (count == 0);
}

bool Queue::isFull() const
{
    return (count >= Capacity);
}