#pragma once



#include "GraphicsManager.h"
#include "InputManager.h"
#include "InputHandler.h"

#include "InputHandlerBaseState.h"
#include "InputHandlerActorFreeCamState.h"

class GameplayManager
{
public:
    GameplayManager();
    ~GameplayManager();

    BOOL Initialize(GraphicsManager * graphics, InputManager * input);
    BOOL Update();
    VOID Termianate();

private:
    GraphicsManager * graphics_;
    InputManager * input_;
    InputHandler * inputHandler_;
    InputHandlerBaseState * state_;
    ActorFreeCam * player_;
    Camera * camera_;
};

