#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer_ = NULL;
    fps_ = NULL;
    cube_ = NULL;
    camera_ = NULL;
    sun_ = NULL;
    windowWidth_ = 0;
    windowHeight_ = 0;
	texture_ = NULL;
}


GraphicsManager::~GraphicsManager()
= default;

BOOL GraphicsManager::InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window)
{
    BOOL result;

    windowWidth_ = window_width;
    windowHeight_ = window_height;

    renderManager_ = new DirectXManager;
    if (!renderManager_) { return FALSE; }
    timer_ = new Timer;
    if (!timer_) { return FALSE; }
    fps_ = new FpsCounter;
    if (!fps_) { return FALSE; }
    cube_ = new StaticMesh;
    if (!cube_) { return FALSE; }
    sun_ = new Light(LightProperties::LIGHT_TYPE_SUN);
    if (!sun_) { return FALSE; }
    //sun_->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    sun_->SetDirection(0.0f, -1.0f, 1.0f);
	texture_ = new Texture;

    result = renderManager_->Initialize(windowWidth_, windowHeight_, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    result = timer_->Launch();
    if (!result) { return FALSE; }
    fps_->Launch();
    result = cube_->CreateMesh(renderManager_->GetDirectXDevice(), &std::wstring(L"house.obj"), LPTSTR(L"color_shader_v.cso"), LPTSTR(L"color_shader_p.cso"));

	std::wstring name(L"texture.dds");
	texture_->LoadFromFile(renderManager_->GetDirectXDevice(), name);

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
    if (cube_)
    {
        cube_->Destroy();
        delete cube_;
        cube_ = NULL;
    }
    if (sun_)
    {
        delete sun_;
        sun_ = NULL;
    }
	if (texture_)
	{
		texture_->Unload();
		delete texture_;
		texture_ = NULL;
	}
}

BOOL GraphicsManager::Update()
{
    // ---------------------------------------------------------------------------
    //camera_->SetPosition(DirectX::XMVectorSet(2.5f, 1.5f, 5.0f, 0.0f));
    //camera_->SetRotation(DirectX::XMVectorSet(15.0f, 207.0f, 0.0f, 0.0f));
    static float zrot = 0.0f;
    zrot += 1.0f;
    if (zrot > 90.0f)
        zrot -= 90.0f;
    //cube_->SetRotation(DirectX::XMVectorSet(0.0f, zrot, 0.0f, 0.0f));
	//sun_->SetDirection(1.0f, 1.0f, 1.0f);
    // ---------------------------------------------------------------------------
    this->Render(camera_);
    timer_->Frame();
    fps_->Frame();
    return TRUE;
}

BOOL GraphicsManager::Render(Camera * camera)
{
    renderManager_->StartScene(0.1f, 0.1f, 0.1f, 1.0f);
    cube_->Render(renderManager_->GetDirectXDeviceContext(), camera, sun_, texture_->Get());
    // TODO : RenderActions
    renderManager_->FinishSceneAndPresent();
    return TRUE;
}

UINT GraphicsManager::GetWindowWidth()
{
    return windowWidth_;
}

UINT GraphicsManager::GetWindowHeight()
{
    return windowHeight_;
}

VOID GraphicsManager::SetRenderCamera(Camera * camera)
{
    camera_ = camera;
}
