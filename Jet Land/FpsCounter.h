#pragma once

#include "IncluderW.h"

class FpsCounter
{
public:
    FpsCounter();
    ~FpsCounter();

    VOID Launch();
    VOID Stop();
    VOID Frame();
    UINT GetFps();
private:
    UINT fpsCount_;
    UINT counter_;
    UINT64 lastSecondTime_;
};

