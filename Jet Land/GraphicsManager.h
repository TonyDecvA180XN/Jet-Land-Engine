#pragma once

#include "IncluderW.h"
#include "RenderManager.h"
#include "Timer.h"
#include "FpsCounter.h"
#include "Camera.h"
#include "PlayerActor.h"
#include "StaticMesh.h"

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    BOOL InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window);
    VOID TerminateGraphicsSystem();

    BOOL Update();

    PlayerActor * GetPlayerActor();

private:
    RenderManager * renderManager_;
    Timer * timer_;
    FpsCounter * fps_;
    PlayerActor * player_;
    Camera * camera_;
    StaticMesh * cube_;
};

