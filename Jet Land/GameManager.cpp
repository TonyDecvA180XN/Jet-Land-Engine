/**
* \file GameManager.cpp
* This file contains implementation of GameManager class.
*
* \author Anton Dospehov
*/

#include "GameManager.h"

/**
 * \details Default initialization of fields.
*/
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

/**
 * \details Creates and launches game systems in order as below:
 *  -# Configuration manager
 *    Reads game settings from settings.ini file.
 *  -# Windows API manager
 *    Creates game window and defines OS messages handlers.
 *  -# Input manager
 *    Creates DirectX 8 input devices for mouse and keyboard control.
 *  -# Graphics manager
 *    Handles DirectX 11 controls, manages rendering.
 *  -# Gameplay manager
 *    Defines game behavior.
 *  -# ...
 *
 * \todo Add another subsystems.
 * \param h_instance Handler to program ex.
 * \return TRUE if success, otherwise FALSE.
 */
BOOL GameManager::Initialize(HINSTANCE h_instance)
{
    BOOL result; ///< result checker

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

/**
 * \details Terminates all subsystems in reversed order of their initiating.
 * See Initialize() method for detalis.
 */
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
    if (gameplayManager_)
    {
        gameplayManager_->Termianate();
        delete gameplayManager_;
        gameplayManager_ = NULL;
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

/**
 * \details Run game loop until something will wrong or the game send stop signal
 * by returning boolean value from Update() methods of all game systems.
*/
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
        result = gameplayManager_->Update();
        if (!result) { isExit_ = TRUE; }
        result = graphicsManager_->Update();
        if (!result) { isExit_ = TRUE; }
    }
}
