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
        BOOL enableVSync;
    } Screen;
};

