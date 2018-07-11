#include "InputHandlerActorFreeCamState.h"


InputHandlerActorFreeCamState::InputHandlerActorFreeCamState(Actor * actor)
    : actor_(actor)
{
}

InputHandlerActorFreeCamState::~InputHandlerActorFreeCamState()
= default;

VOID InputHandlerActorFreeCamState::AttachActor(Actor * actor)
{
    actor_ = actor;
}

VOID InputHandlerActorFreeCamState::HandleInput(InputManager * input)
{
    if (input->IsKeyboardKeyPressed(DIK_W))
    {
        actor_->Move(DirectX::XMVectorSet(0.0f, 0.0f, 0.5f, 0.0f));
    } 
    if (input->IsKeyboardKeyPressed(DIK_S))
    {
        actor_->Move(DirectX::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f));
    }
    if (input->IsKeyboardKeyPressed(DIK_A))
    {
        actor_->Move(DirectX::XMVectorSet(-0.5f, 0.0f, 0.0f, 0.0f));
    }
    if (input->IsKeyboardKeyPressed(DIK_D))
    {
        actor_->Move(DirectX::XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f));
    }
    if (input->IsKeyboardKeyPressed(DIK_Q))
    {
        actor_->Move(DirectX::XMVectorSet(0.0f, -0.5f, 0.0f, 0.0f));
    }
    if (input->IsKeyboardKeyPressed(DIK_E))
    {
        actor_->Move(DirectX::XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f));
    }

    int dx, dy;
    input->GetMouseDelta(dx, dy);
    actor_->TurnAround(DirectX::XMVectorSet(FLOAT(dy) / 4.0f, FLOAT(dx) / 4.0f, 0.0f, 0.0f));
}
