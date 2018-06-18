#pragma once

#include "WindowsManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    BOOL Initialize(HINSTANCE h_instance);
    VOID Terminate();

    VOID Execute();
private:
    WindowsManager * windowsManager_;
    BOOL isExit_;
};

