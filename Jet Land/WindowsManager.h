#pragma once

#include <Windows.h>

class WindowsManager
{
public:
    WindowsManager();
    ~WindowsManager();

    VOID CreateGameWindow(HINSTANCE h_instance, UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL use_force_resolution);
    VOID DestroyGameWindow();

    BOOL Update();
    HWND GetWindowHandle() const { return windowHandle_; }
private:
    BOOL enableFullscreen_;
    UINT windowWidth_;
    UINT windowHeight_;
    HWND windowHandle_;
    HINSTANCE hInstance_;
    MSG windowsMessage_;
};

static LRESULT CALLBACK WndProc(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam);