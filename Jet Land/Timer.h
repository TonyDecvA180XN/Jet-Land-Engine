#pragma once



class Timer
{
public:
    Timer();
    ~Timer();

    BOOL Launch();
    VOID Stop();

    VOID Frame();

    INT64 GetLaunchTime();
    INT64 GetLastFrameTime();
    FLOAT GetFrameTime();

private:
    INT64 launchTime_;
    INT64 lastFrameTime_;
    INT64 frequency_;
    FLOAT frequencyPerMs_;
    FLOAT frameTime_;
};

