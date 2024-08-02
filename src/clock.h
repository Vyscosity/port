#pragma once

#include <SDL.h>
#include "types.h"

class Clock {
public:
    Clock();

    float restart();
    float getElapsedTime();

private:
    u64 startTime_;
    double frequency_;
};