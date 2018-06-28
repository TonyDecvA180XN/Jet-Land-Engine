#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer_ = NULL;
    fps_ = NULL;
    camera_ = NULL;
    object_ = NULL;
}


GraphicsManager::~GraphicsManager()
= default;

BOOL GraphicsManager::InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window)
{
    BOOL result;

    renderManager_ = new RenderManager;
    if (!renderManager_) { return FALSE; }
    timer_ = new Timer;
    if (!timer_) { return FALSE; }
    fps_ = new FpsCounter;
    if (!fps_) { return FALSE; }
    camera_ = new Camera;
    if (!camera_) { return FALSE; }
    object_ = new Object;
    if (!object_) { return FALSE; }

    result = renderManager_->Initialize(window_width, window_height, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    camera_->Create(45.0f, window_width, window_height, 0.1f, 1000.0f);
    result = timer_->Launch();
    if (!result) { return FALSE; }
    fps_->Launch();
    result = object_->CreateMesh(renderManager_->GetDirectXDevice());
    if (!result) { return FALSE; }
    result = object_->CreateMaterial(renderManager_->GetDirectXDevice(), LPTSTR(L"color_shader.fx"), LPTSTR(L"color_shader.fx"));
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
    if (timer_)
    {
        timer_->Stop();
        delete timer_;
        timer_ = NULL;
    }
    if (fps_)
    {
        fps_->Stop();
        delete fps_;
        fps_ = NULL;
    }
    if (camera_)
    {
        delete camera_;
        camera_ = NULL;
    }
    if (object_)
    {
        object_->DestroyMesh();
        object_->DestroyMaterial();
        delete object_;
        object_ = NULL;
    }
}

BOOL GraphicsManager::Update()
{
    // ---------------------------------------------------------------------------
    camera_->SetPosition(2.5f, 1.5f, 5.0f);
    camera_->SetRotation(15.0f, 207.0f, 0.0f);
    // ---------------------------------------------------------------------------
    renderManager_->StartScene(0.1f, 0.1f, 0.1f, 1.0f);
    camera_->Frame();
    object_->Render(renderManager_->GetDirectXDeviceContext(), DirectX::XMMatrixIdentity(), camera_->GetViewMatrix(), camera_->GetProjMatrix());
    // TODO : RenderActions
    renderManager_->FinishSceneAndPresent();
    timer_->Frame();
    fps_->Frame();
    return TRUE;
}
