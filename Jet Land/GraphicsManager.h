#pragma once

#include "IncluderW.h"
#include "RenderManager.h"
#include "Timer.h"
#include "FpsCounter.h"
#include "Camera.h"
#include "ActorFreeCam.h"
#include "StaticMesh.h"

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    BOOL InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window);
    VOID TerminateGraphicsSystem();

    BOOL Update();

    ActorFreeCam * GetPlayerActor();

private:
    RenderManager * renderManager_;
    Timer * timer_;
    FpsCounter * fps_;
    ActorFreeCam * player_;
    Camera * camera_;
    StaticMesh * cube_;
};

