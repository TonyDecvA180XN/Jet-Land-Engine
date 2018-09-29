#pragma once


#include "DirectXManager.h"
#include "Timer.h"
#include "FpsCounter.h"
#include "Camera.h"
#include "ActorFreeCam.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "LightSource.h"
#include "Pool.h"
#include "LocationManager.h"


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

    VOID SetRenderCamera(Camera * camera);

private:
    DirectXManager * renderManager_;
    Camera * camera_;
	Pool<Light> * m_lights;
	Pool<StaticMesh> * m_meshes;
    Light * sun_;
    Timer * timer_;
    FpsCounter * fps_;
    StaticMesh * cube_;
    UINT windowWidth_, windowHeight_;
	Texture * texture_;
	LocationManager * m_locManager;
};

