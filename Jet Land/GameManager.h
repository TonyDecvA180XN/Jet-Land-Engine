#pragma once

#include "WindowsManager.h"
#include "ConfigManager.h"

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
    ConfigManager * configManager_;
    Configuration * config_;
    BOOL isExit_;
};

