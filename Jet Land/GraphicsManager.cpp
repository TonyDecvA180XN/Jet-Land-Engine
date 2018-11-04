#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{
    renderManager_ = NULL;
    timer_ = NULL;
    fps_ = NULL;
    camera_ = NULL;
	
	m_lightComp = NULL;
	m_staticMeshes = NULL;
	m_geometries = NULL;
	m_materials = NULL;
	m_textures = NULL;
	m_shaders = NULL;

    windowWidth_ = 0;
    windowHeight_ = 0;
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
	camera_ = new Camera;

	m_lightComp = new LightCommonComponent;
	m_staticMeshes = new Pool<StaticMesh>(LIMIT_AMOUNT_OF_STATIC_MESHES);
	m_geometries = new Pool<Mesh>(LIMIT_AMOUNT_OF_MESHES);
	m_materials = new Pool<Material>(LIMIT_AMOUNT_OF_MATERIALS);
	m_textures = new Pool<Texture>(LIMIT_AMOUNT_OF_TEXTURES);
	m_shaders = new Pool<CompiledShader>(LIMIT_AMOUNT_OF_SHADERS);

    result = renderManager_->Initialize(windowWidth_, windowHeight_, enable_fullscreen, enable_vsync, msaa_count, h_window);
    if (!result) { return FALSE; }
    result = timer_->Launch();
    if (!result) { return FALSE; }
    fps_->Launch();
	camera_->Create(45.0f, windowWidth_, windowHeight_, 0.1f, 1000.0f);
	m_lightComp->Create(renderManager_->GetDirectXDevice());

	Loader::LoadLocation(
		renderManager_->GetDirectXDevice(),
		"location.xml",
		m_staticMeshes,
		m_geometries,
		m_textures,
		m_lightComp,
		m_materials,
		camera_,
		m_shaders
	);

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
	m_lightComp->Update(renderManager_->GetDirectXDeviceContext());
    this->Render(camera_);
    timer_->Frame();
    fps_->Frame();
    return TRUE;
}

BOOL GraphicsManager::Render(Camera * camera)
{
    renderManager_->StartScene(0.1f, 0.1f, 0.1f, 1.0f);
	for (UINT i = 0; i < LIMIT_AMOUNT_OF_STATIC_MESHES; ++i)
	{
		StaticMesh * item = m_staticMeshes->GetItem(i);
		if (item->IsActive())
		{
			item->Render(renderManager_->GetDirectXDeviceContext());
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

Camera * GraphicsManager::GetCamera()
{
	return camera_;
}
