#include "clock.h"

Clock::Clock() {
    frequency_ = 1.0 / SDL_GetPerformanceFrequency();
    restart();
}

float Clock::restart() {
    u64 now = SDL_GetPerformanceCounter();
    float elapsed = (now - startTime_) * frequency_;
    startTime_ = now;
    return elapsed;
}

float Clock::getElapsedTime() {
    u64 now = SDL_GetPerformanceCounter();
    return (now - startTime_) * frequency_;
}