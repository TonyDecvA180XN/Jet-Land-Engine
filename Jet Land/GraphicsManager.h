#pragma once

#include "IncluderW.h"
#include "RenderManager.h"
#include "Timer.h"
#include "FpsCounter.h"

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    BOOL InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window);
    VOID TerminateGraphicsSystem();

    BOOL Update();

private:
    RenderManager * renderManager_;
    Timer * timer;
    FpsCounter * fps;
};

