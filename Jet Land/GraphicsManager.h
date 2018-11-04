#pragma once

#include "Utils.h"
#include "Globals.h"
#include "Loader.h"
#include "DirectXManager.h"
#include "Timer.h"
#include "FpsCounter.h"
#include "Camera.h"
#include "ActorFreeCam.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "CompiledShader.h"
#include "Pool.h"
#include "LightCommonComponent.h"


class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    BOOL InitializeGraphicsSystem(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window);
    VOID TerminateGraphicsSystem();

    BOOL Update();

    BOOL Render(Camera * camera);

    UINT GetWindowWidth();
    UINT GetWindowHeight();

    Camera * GetCamera();

private:
    DirectXManager * renderManager_;
    Camera * camera_;
	LightCommonComponent * m_lightComp;

	Pool<StaticMesh> * m_staticMeshes;
	Pool<Mesh> * m_geometries;
	Pool<Material> * m_materials;
	Pool<Texture> * m_textures;
	Pool<CompiledShader> * m_shaders;

    Timer * timer_;
    FpsCounter * fps_;
    UINT windowWidth_, windowHeight_;
};

