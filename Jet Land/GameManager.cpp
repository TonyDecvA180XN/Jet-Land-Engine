#include "GameManager.h"



GameManager::GameManager()
{
    windowsManager_ = new WindowsManager;
    configManager_ = new ConfigManager;
    config_ = NULL;
    isExit_ = FALSE;
}


GameManager::~GameManager()
= default;

BOOL GameManager::Initialize(HINSTANCE h_instance)
{
    config_ = new Configuration;

    configManager_->LoadConfig(LPSTR("config.ini"));
    configManager_->ApplyConfig(config_);

    windowsManager_->CreateGameWindow(
        h_instance,
        config_->Screen.windowWidth,
        config_->Screen.windowHeight,
        config_->Screen.enableFullscreen,
        config_->Screen.useForceResolution
    );

    return TRUE;
}

VOID GameManager::Terminate()
{
    if (windowsManager_)
    {
        windowsManager_->DestroyGameWindow();
        delete windowsManager_;
        windowsManager_ = NULL;
    }
    if (configManager_)
    {
        configManager_->DeleteConfig();
        delete configManager_;
        configManager_ = NULL;
    }
    if (config_)
    {
        delete config_;
        config_ = NULL;
    }
}

VOID GameManager::Execute()
{
    while (!isExit_)
    {
        BOOL result;

        result = windowsManager_->Update();
        if (!result) {isExit_ = TRUE;}
        Sleep(5);
    }
}
