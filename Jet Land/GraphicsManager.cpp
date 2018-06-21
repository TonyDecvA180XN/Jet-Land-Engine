#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
}


GraphicsManager::~GraphicsManager()
= default;

BOOL GraphicsManager::InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window)
{
    BOOL result;

    renderManager_ = new RenderManager;
    if (!renderManager_) { return FALSE; }

    result = renderManager_->Initialize(window_width, window_height, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }

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
    return TRUE;
}
