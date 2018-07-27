/**
 * \file GameManager.h
 * This file contains declaration of GameManager class.
 *
 * \author Anton Dospehov
 */

#pragma once

#include "ConfigManager.h"
#include "GameplayManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "WindowsManager.h"

 /**
  * \class GameManager
  * \brief Class used to manage all in-game subsystems.
  *
  * \details This class launches all subsystems and handle them on runtime.
  * It controls it's launching, updating and terminating.
  * The manager privides handling for:
  *  - game window
  *  - audio
  *  - physics
  *  - input
  *  - graphics and etc.
  *
  * For main handling use three functions: Initialize(), Execute(), Terminate().
  */
class GameManager
{
public:
    /**
     * \brief Standard constructor.
     */
    GameManager();

    /**
     * \brief Standard destructor.
     */
    ~GameManager();

    /**
    * \brief Common initializer.
    */
    BOOL Initialize(HINSTANCE h_instance);

    /**
    * \brief Common terminator.
    */
    VOID Terminate();

    /**
    * \brief Game loop function.
    */
    VOID Execute();

private:
    ConfigManager * configManager_;
    WindowsManager* windowsManager_;
    InputManager * inputManager_;
    GraphicsManager * graphicsManager_;
    GameplayManager * gameplayManager_;
    Configuration * config_;
    BOOL isExit_;
};
