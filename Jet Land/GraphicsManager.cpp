#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer_ = NULL;
    fps_ = NULL;
    player_ = NULL;
    camera_ = NULL;
    cube_ = NULL;
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
    player_ = new ActorFreeCam;
    if (!player_) { return FALSE; }
    cube_ = new StaticMesh;
    if (!cube_) { return FALSE; }

    result = renderManager_->Initialize(window_width, window_height, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    camera_->Create(45.0f, window_width, window_height, 0.1f, 1000.0f);
    player_->SetCamera(camera_);
    player_->SetPosition(0.0f, 0.0f, 10.0f);
    player_->SetRotation(0.0f, 15.0f, 0.0f);
    player_->Update(0);
    result = timer_->Launch();
    if (!result) { return FALSE; }
    fps_->Launch();
    result = cube_->CreateMesh(renderManager_->GetDirectXDevice());
    if (!result) { return FALSE; }
    result = cube_->CreateMaterial(renderManager_->GetDirectXDevice(), LPTSTR(L"color_shader.fx"));
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
    if (player_)
    {
        delete player_;
        player_ = NULL;
    }
    if (cube_)
    {
        cube_->Destroy();
        delete cube_;
        cube_ = NULL;
    }
}

BOOL GraphicsManager::Update()
{
    // ---------------------------------------------------------------------------
    //camera_->SetPosition(DirectX::XMVectorSet(2.5f, 1.5f, 5.0f, 0.0f));
    //camera_->SetRotation(DirectX::XMVectorSet(15.0f, 207.0f, 0.0f, 0.0f));
    //static float zrot = 50;
    //zrot -= 1.0f;
    //if (zrot < -50.0f)
    //    zrot += 100.0f;
    //cube_->SetRotation(DirectX::XMVectorSet(0.0f, zrot, 0.0f, 0.0f));
    // ---------------------------------------------------------------------------
    renderManager_->StartScene(0.1f, 0.1f, 0.1f, 1.0f);
    player_->Update(1);
    cube_->Render(renderManager_->GetDirectXDeviceContext(), player_->GetCamera());
    // TODO : RenderActions
    renderManager_->FinishSceneAndPresent();
    timer_->Frame();
    fps_->Frame();
    return TRUE;
}

ActorFreeCam * GraphicsManager::GetPlayerActor()
{
    return player_;
}
