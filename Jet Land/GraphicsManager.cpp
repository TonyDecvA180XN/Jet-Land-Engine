#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer_ = NULL;
    fps_ = NULL;
    cube_ = NULL;
    camera_ = NULL;
    sun_ = NULL;
	m_lights = NULL;
	m_meshes = NULL;
    windowWidth_ = 0;
    windowHeight_ = 0;
	texture_ = NULL;
	m_locManager = NULL;
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
    //cube_ = new StaticMesh;
    //if (!cube_) { return FALSE; }
	m_lights = new Pool<Light>(10);
	if (!m_lights) { return FALSE; }
	m_meshes = new Pool<StaticMesh>(10);
	if (!m_meshes) { return FALSE; }
	//m_lights->Allocate(&sun_);
	//m_meshes->Allocate(&cube_);
	////m_lights->Release(sun_); // danger
 //   if (!sun_) { return FALSE; }
 //   //sun_->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
 //   sun_->SetDirection(0.0f, -1.0f, 1.0f);

	

	texture_ = new Texture;

    result = renderManager_->Initialize(windowWidth_, windowHeight_, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    result = timer_->Launch();
    if (!result) { return FALSE; }
    fps_->Launch();
    //result = cube_->CreateMesh(renderManager_->GetDirectXDevice(), &std::wstring(L"house.obj"), LPTSTR(L"color_shader_v.cso"), LPTSTR(L"color_shader_p.cso"));
	m_locManager = new LocationManager;
	if (!m_locManager) { return FALSE; }
	m_locManager->Connect(m_meshes);
	m_locManager->Connect(m_lights);

	result = m_locManager->LoadFromFile(renderManager_->GetDirectXDevice(), LPSTR("location.xml"));
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
    /*if (cube_)
    {
        cube_->Destroy();
        delete cube_;
        cube_ = NULL;
    }*/
    /*if (sun_)
    {
        delete sun_;
        sun_ = NULL;
    }*/
	if (m_locManager)
	{
		m_locManager->UnloadAll();
		m_locManager->Disconnect();
		delete m_locManager;
		m_locManager = NULL;
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
    /*static float zrot = 0.0f;
    zrot += 1.0f;
    if (zrot > 90.0f)
        zrot -= 90.0f;
    *///cube_->SetRotation(DirectX::XMVectorSet(0.0f, zrot, 0.0f, 0.0f));
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
    //cube_->Render(renderManager_->GetDirectXDeviceContext(), camera, sun_, texture_->Get());
    // TODO : RenderActions
	for (auto mesh = m_meshes->Begin(); mesh != m_meshes->End(); ++mesh)
	{
		if (mesh->IsActive())
		{
			mesh->Render(renderManager_->GetDirectXDeviceContext(), camera, (Light *)&(*(m_lights->Begin())), texture_->Get());
		}
	}
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
