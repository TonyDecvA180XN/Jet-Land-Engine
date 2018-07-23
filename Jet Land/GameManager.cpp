#include "GameManager.h"



GameManager::GameManager()
{
    configManager_ = NULL;
    windowsManager_ = NULL;
    inputManager_ = NULL;
    graphicsManager_ = NULL;
    gameplayManager_ = NULL;
    config_ = NULL;
    isExit_ = FALSE;
}


GameManager::~GameManager()
= default;

BOOL GameManager::Initialize(HINSTANCE h_instance)
{
    BOOL result;

    configManager_ = new ConfigManager;
    if (!configManager_) { return FALSE; }
    windowsManager_ = new WindowsManager;
    if (!windowsManager_) { return FALSE; }
    inputManager_ = new InputManager;
    if (!inputManager_) { return FALSE; }
    graphicsManager_ = new GraphicsManager;
    if (!graphicsManager_) { return FALSE; }
    gameplayManager_ = new GameplayManager;
    if (!gameplayManager_) { return FALSE; }
    config_ = new Configuration;
    if (!config_) { return FALSE; }
    result = configManager_->LoadConfig(LPSTR("config.ini"));
    if (!result) { return FALSE; }
    configManager_->ApplyConfig(config_);

    windowsManager_->CreateGameWindow(
        h_instance,
        config_->Screen.windowWidth,
        config_->Screen.windowHeight,
        config_->Screen.enableFullscreen,
        config_->Screen.useForceResolution,
        config_->Screen.enableBorderlessWindow,
        config_->Screen.hideCursor
    );

    result = inputManager_->InitializeDevices(h_instance, windowsManager_->GetWindowHandle());
    if (!result) { return FALSE; }

    result = graphicsManager_->InitializeGraphicsSystem(
        config_->Screen.windowWidth,
        config_->Screen.windowHeight,
        config_->Screen.enableFullscreen,
        config_->Screen.enableVSync,
        config_->Screen.multiSampleAACount,
        windowsManager_->GetWindowHandle());
    if (!result) { return FALSE; }

    result = gameplayManager_->Initialize(graphicsManager_, inputManager_);
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
    if (gameplayManager_)
    {
        gameplayManager_->Termianate();
        delete gameplayManager_;
        gameplayManager_ = NULL;
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
        result = gameplayManager_->Update();
        if (!result) { isExit_ = TRUE; }
        if (inputManager_->IsKeyboardKeyPressed(DIK_ESCAPE)) { isExit_ = TRUE; }
        result = graphicsManager_->Update();
        if (!result) { isExit_ = TRUE; }
    }
}
