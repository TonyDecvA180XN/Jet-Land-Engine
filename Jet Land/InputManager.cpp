#include "InputManager.h"


#include <comdef.h>

InputManager::InputManager()
{
    dInputDevice_ = NULL;
    keyboard_ = NULL;
    mouse_ = NULL;
    ZeroMemory(&keyboardState_, sizeof keyboardState_);
    mouseState_ = DIMOUSESTATE();
}


InputManager::~InputManager()
= default;

BOOL InputManager::InitializeDevices(HINSTANCE h_instance, HWND h_window)
{
    HRESULT result;
    result = DirectInput8Create(h_instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&dInputDevice_, NULL);
    if (FAILED(result)) { return FALSE; }
    result = dInputDevice_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
    if (FAILED(result)) { return FALSE; }
    result = keyboard_->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) { return FALSE; }
    result = keyboard_->SetCooperativeLevel(h_window, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(result)) { return FALSE; }
    result = keyboard_->Acquire();
	/*if (FAILED(result))
	{
		MessageBox(h_window, _com_error(result).ErrorMessage(), L"ERROR", MB_ICONERROR);
	}*/
    //if (FAILED(result)) { return FALSE; }
    result = dInputDevice_->CreateDevice(GUID_SysMouse, &mouse_, NULL);
    if (FAILED(result)) { return FALSE; }
    result = mouse_->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) { return FALSE; }
    result = mouse_->SetCooperativeLevel(h_window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(result)) { return FALSE; }
    result = mouse_->Acquire();
    if (FAILED(result)) { return FALSE; }

    return true;
}

VOID InputManager::TerminateDevices()
{
    if (keyboard_)
    {
        keyboard_->Unacquire();
        keyboard_->Release();
        keyboard_ = NULL;
    }
    if (mouse_)
    {
        mouse_->Unacquire();
        mouse_->Release();
        mouse_ = NULL;
    }

    if (dInputDevice_)
    {
        dInputDevice_->Release();
        dInputDevice_ = NULL;
    }
}

BOOL InputManager::Update()
{
    HRESULT result;
    result = keyboard_->GetDeviceState(sizeof keyboardState_, &keyboardState_);
    if (FAILED(result))
    {
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
        {
            keyboard_->Acquire();
        }
        else { return FALSE; }
    }
    result = mouse_->GetDeviceState(sizeof DIMOUSESTATE, &mouseState_);
    if (FAILED(result))
    {
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
        {
            mouse_->Acquire();
        }
        else { return FALSE; }
    }

    return TRUE;
}

VOID InputManager::GetMouseDelta(INT& x, INT& y)
{
    x = mouseState_.lX;
    y = mouseState_.lY;
}

BOOL InputManager::IsKeyboardKeyPressed(BYTE key)
{
    return keyboardState_[key] & 0b10000000;
}
