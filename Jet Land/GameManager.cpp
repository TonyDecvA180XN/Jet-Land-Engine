#include "GameManager.h"



GameManager::GameManager()
{
    configManager_ = new ConfigManager;
    windowsManager_ = new WindowsManager;
    inputManager_ = new InputManager;
    graphicsManager_ = new GraphicsManager;
    config_ = NULL;
    isExit_ = FALSE;
}


GameManager::~GameManager()
= default;

BOOL GameManager::Initialize(HINSTANCE h_instance)
{
    BOOL result;

    config_ = new Configuration;
    result = configManager_->LoadConfig(LPSTR("config.ini"));
    if (!result) { return FALSE; }
    configManager_->ApplyConfig(config_);

    windowsManager_->CreateGameWindow(
        h_instance,
        config_->Screen.windowWidth,
        config_->Screen.windowHeight,
        config_->Screen.enableFullscreen,
        config_->Screen.useForceResolution,
        config_->Screen.enableBorderlessWindow
    );

    result = inputManager_->InitializeDevices(h_instance, windowsManager_->GetWindowHandle());
    if (!result) { return FALSE; }

    result = graphicsManager_->InitializeGraphicsSystem();
    if (!result) { return FALSE; }

    return TRUE;
}

VOID GameManager::Terminate()
{
    if (configManager_)
    {
        configManager_->DeleteConfig();
        delete configManager_;
        configManager_ = NULL;
    }
    if (windowsManager_)
    {
        windowsManager_->DestroyGameWindow();
        delete windowsManager_;
        windowsManager_ = NULL;
    }
    if (inputManager_)
    {
        inputManager_->TerminateDevices();
        delete inputManager_;
        inputManager_ = NULL;
    }
    if (graphicsManager_)
    {
        graphicsManager_->TerminateGraphicsSystem();
        delete graphicsManager_;
        graphicsManager_ = NULL;
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
        if (!result) { isExit_ = TRUE; }
        result = inputManager_->Update();
        if (!result) { isExit_ = TRUE; }
        if (inputManager_->IsKeyboardKeyPressed(DIK_ESCAPE)) { isExit_ = TRUE; }
        result = graphicsManager_->Update();
        if (!result) { isExit_ = TRUE; }
        Sleep(5);
    }
}
