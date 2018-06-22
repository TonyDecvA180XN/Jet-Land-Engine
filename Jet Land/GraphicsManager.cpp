#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer = NULL;
    fps = NULL;
}


GraphicsManager::~GraphicsManager()
= default;

BOOL GraphicsManager::InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window)
{
    BOOL result;

    renderManager_ = new RenderManager;
    if (!renderManager_) { return FALSE; }
    timer = new Timer;
    if (!timer) { return FALSE; }
    fps = new FpsCounter;
    if (!fps) { return FALSE; }

    result = renderManager_->Initialize(window_width, window_height, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    result = timer->Launch();
    if (!result) { return FALSE; }
    fps->Launch();
    

    return TRUE;
}

VOID GraphicsManager::TerminateGraphicsSystem()
{
    if (renderManager_)
    {
        renderManager_->Terminate();
        delete renderManager_;
        renderManager_ = NULL;
    }
    if (timer)
    {
        timer->Stop();
        delete timer;
        timer = NULL;
    }
    if (fps)
    {
        fps->Stop();
        delete fps;
        fps = NULL;
    }
}

BOOL GraphicsManager::Update()
{
    // ---------------------------------------------------------------------------
    static float color = 0.0f;
    color += 0.004f;
    if (color >= 1.0f)
    {
        color = 0.0f;
    }
    // ---------------------------------------------------------------------------
    renderManager_->StartScene(color, color, color, 1.0f);
    // TODO : RenderActions
    renderManager_->FinishSceneAndPresent();
    timer->Frame();
    fps->Frame();
    return TRUE;
}
