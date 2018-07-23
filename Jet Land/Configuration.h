#pragma once

#include "IncluderW.h"

struct Configuration
{
    struct ScreenSettings
    {
        UINT windowWidth;
        UINT windowHeight;
        BOOL enableFullscreen;
        BOOL useForceResolution;
        BOOL enableBorderlessWindow;
        BOOL hideCursor;
        BOOL enableVSync;
        UINT multiSampleAACount;
    } Screen;
};

