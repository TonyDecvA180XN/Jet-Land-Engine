#include "WindowsManager.h"



WindowsManager::WindowsManager()
{
    hInstance_ = NULL;
    windowHandle_ = NULL;
    windowsMessage_ = MSG{NULL};
    enableFullscreen_ = FALSE;
    windowWidth_ = 0;
    windowHeight_ = 0;
}


WindowsManager::~WindowsManager()
= default;

VOID WindowsManager::CreateGameWindow(HINSTANCE h_instance, UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL use_force_resolution)
{
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof windowClass;
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = h_instance;
    windowClass.hIcon = LoadIcon(h_instance, L"IDI_MAIN_ICON");
    windowClass.hIconSm = LoadIcon(h_instance, L"IDI_MAIN_ICON");
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
    windowClass.lpszClassName = L"Jet Land Window Class";
    windowClass.lpszMenuName = NULL;
    RegisterClassEx(&windowClass);

    SetProcessDPIAware();

    UINT displayWidth = GetSystemMetrics(SM_CXSCREEN);
    UINT displayHeight = GetSystemMetrics(SM_CYSCREEN);
    windowWidth_ = window_width;
    windowHeight_ = window_height;
    enableFullscreen_ = enable_fullscreen;
    hInstance_ = h_instance;

    if (enableFullscreen_ && !use_force_resolution)
    {
        windowWidth_ = displayWidth;
        windowHeight_ = displayHeight;
    }
    UINT windowPosX = 0;
    UINT windowPosY = 0;

    if (enableFullscreen_)
    {
        DEVMODE windowSettings;
        ZeroMemory(&windowSettings, sizeof windowSettings);
        windowSettings.dmBitsPerPel = 32;
        windowSettings.dmPelsWidth = windowWidth_;
        windowSettings.dmPelsHeight = windowHeight_;
        windowSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        windowSettings.dmSize = sizeof windowSettings;

        ChangeDisplaySettings(&windowSettings, CDS_FULLSCREEN);
    }
    else
    {
        windowPosX = (displayWidth - window_width) / 2;
        windowPosY = (displayHeight - window_height) / 2;
    }

    windowHandle_ = CreateWindowEx(
        WS_EX_APPWINDOW,
        L"Jet Land Window Class",
        L"Jet Land",
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
        windowPosX,
        windowPosY,
        windowWidth_,
        windowHeight_,
        NULL,
        NULL,
        h_instance,
        NULL);

    ShowWindow(windowHandle_, SW_SHOW);
    SetForegroundWindow(windowHandle_);
    SetFocus(windowHandle_);
}

VOID WindowsManager::DestroyGameWindow()
{
    if (enableFullscreen_)
    {
        ChangeDisplaySettings(NULL, 0);
    }
    DestroyWindow(windowHandle_);
    windowHandle_ = NULL;

    UnregisterClass(L"Hello", hInstance_);
    hInstance_ = NULL;
}

BOOL WindowsManager::Update()
{
    if (PeekMessage(&windowsMessage_, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&windowsMessage_);
        DispatchMessage(&windowsMessage_);
    }

    if (windowsMessage_.message == WM_QUIT)
    {
        return FALSE;
    }

    return TRUE;
}

LRESULT WndProc(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(window_handle, message, wparam, lparam);
    }
}
