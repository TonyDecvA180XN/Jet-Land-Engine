#pragma once

#include "Includer.h"

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

