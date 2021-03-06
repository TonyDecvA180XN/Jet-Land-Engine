#include "GameplayManager.h"



GameplayManager::GameplayManager()
{
    graphics_ = NULL;
    input_ = NULL;
    inputHandler_ = NULL;
    state_ = NULL;
    player_ = NULL;
    camera_ = NULL;
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
    player_ = new ActorFreeCam;
    if (!player_) { return FALSE; }
    state_ = new InputHandlerActorFreeCamState(player_);
    if (!state_) { return FALSE; }
    

	camera_ = graphics->GetCamera();
    player_->SetCamera(camera_);
    camera_->SetPosition(0.0f, 6.0f, 16.0f);
    camera_->Rotate(8.0f, 207.0f, 0.0f);
    player_->Update(0);


    inputHandler_->SetState(state_);

    return TRUE;
}

BOOL GameplayManager::Update()
{
    inputHandler_->Handle();
    player_->Update(1);
    return TRUE;
}

VOID GameplayManager::Termianate()
{
    if (inputHandler_)
    {
        delete inputHandler_;
        inputHandler_ = NULL;
    }
    if (camera_)
    {
        delete camera_;
        camera_ = NULL;
    }
    if (player_)
    {
        delete player_;
        player_ = NULL;
    }
}
