#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

class InputManager
{
public:
    InputManager();
    ~InputManager();

    BOOL InitializeDevices(HINSTANCE h_instance, HWND h_window);
    VOID TerminateDevices();

    BOOL Update();

    VOID GetMouseDelta(INT& x, INT& y);
    BOOL IsKeyboardKeyPressed(BYTE key);

private:
    IDirectInput8 * dInputDevice_;
    IDirectInputDevice8 * keyboard_;
    IDirectInputDevice8 * mouse_;

    BYTE keyboardState_[256];
    DIMOUSESTATE mouseState_;
};

