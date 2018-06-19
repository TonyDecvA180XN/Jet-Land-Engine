#pragma once

#include "ConfigManager.h"
#include "WindowsManager.h"
#include "InputManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    BOOL Initialize(HINSTANCE h_instance);
    VOID Terminate();

    VOID Execute();
private:
    ConfigManager * configManager_;
    WindowsManager * windowsManager_;
    InputManager * inputManager_;
    Configuration * config_;
    BOOL isExit_;
};

