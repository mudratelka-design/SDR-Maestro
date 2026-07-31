//=============================================================================
// File: EncoderManager.h
// Commit: 2
//=============================================================================

#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

class EncoderManager
{
public:
    void begin();
    void update();

private:
    int lastState = 0;
};

#endif
