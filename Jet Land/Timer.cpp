#include "Timer.h"



Timer::Timer()
{
    launchTime_ = 0;
    frequency_ = 0;
    lastFrameTime_ = 0;
    frequencyPerMs_ = 0.0f;
    frameTime_ = 0.0f;
}


Timer::~Timer()
{
}

BOOL Timer::Launch()
{
    QueryPerformanceFrequency((LARGE_INTEGER *)(&frequency_));
    if (frequency_ == 0) { return FALSE; }
    frequencyPerMs_ = FLOAT(frequency_) / 1000.0f;
    QueryPerformanceCounter((LARGE_INTEGER *)(&launchTime_));
    lastFrameTime_ = launchTime_;

    return TRUE;
}

VOID Timer::Stop()
{
    return;
}

VOID Timer::Frame()
{
    INT64 currentFrametime;
    QueryPerformanceCounter((LARGE_INTEGER *)&currentFrametime);
    frameTime_ = FLOAT(currentFrametime - lastFrameTime_) / frequencyPerMs_;
    lastFrameTime_ = currentFrametime;
}

INT64 Timer::GetLaunchTime()
{
    return launchTime_;
}

INT64 Timer::GetLastFrameTime()
{
    return lastFrameTime_;
}

FLOAT Timer::GetFrameTime()
{
    return frameTime_;
}

