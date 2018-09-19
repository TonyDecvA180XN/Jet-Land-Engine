#pragma once



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

