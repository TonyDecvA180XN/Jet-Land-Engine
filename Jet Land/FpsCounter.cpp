#include "FpsCounter.h"



FpsCounter::FpsCounter()
{
    counter_ = 0;
    fpsCount_ = 0;
    lastSecondTime_ = 0;
}


FpsCounter::~FpsCounter()
{
}

VOID FpsCounter::Launch()
{
    counter_ = 0;
    fpsCount_ = 0;
    lastSecondTime_ = 0;
}

VOID FpsCounter::Stop()
{
    return;
}

VOID FpsCounter::Frame()
{
    counter_++;

    if (GetTickCount64() >= lastSecondTime_ + 1000)
    {
        fpsCount_ = counter_;
        counter_ = 0;
        lastSecondTime_ = GetTickCount64();
    }
}

UINT FpsCounter::GetFps()
{
    return fpsCount_;
}
