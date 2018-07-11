#include "GameplayManager.h"



GameplayManager::GameplayManager()
{
    graphics_ = NULL;
    input_ = NULL;
    inputHandler_ = NULL;
    state_ = NULL;
}


GameplayManager::~GameplayManager()
{
}

BOOL GameplayManager::Initialize(GraphicsManager * graphics, InputManager * input)
{
    graphics_ = graphics;
    input_ = input;

    inputHandler_ = new InputHandler(input_);
    if (!inputHandler_) { return FALSE; }

    state_ = new InputHandlerActorFreeCamState(graphics_->GetPlayerActor());
    if (!state_) { return FALSE; }

    inputHandler_->SetState(state_);

    return TRUE;
}

BOOL GameplayManager::Update()
{
    inputHandler_->Handle();

    return TRUE;
}

VOID GameplayManager::Termianate()
{
    if (inputHandler_)
    {
        delete inputHandler_;
        inputHandler_ = NULL;
    }
}
