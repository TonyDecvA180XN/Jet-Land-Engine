#include "InputHandlerActorFreeCamState.h"


InputHandlerActorFreeCamState::InputHandlerActorFreeCamState(ActorFreeCam * actor)
    : actor_(actor)
{
}

InputHandlerActorFreeCamState::~InputHandlerActorFreeCamState()
= default;

VOID InputHandlerActorFreeCamState::AttachActor(ActorFreeCam * actor)
{
    actor_ = actor;
}

VOID InputHandlerActorFreeCamState::HandleInput(InputManager * input)
{
    FLOAT velocity = 0.2f;
    if (input->IsKeyboardKeyPressed(DIK_LSHIFT))
    {
        velocity *= 4;
    } else if (input->IsKeyboardKeyPressed(DIK_LALT))
    {
        velocity /= 4;
    }
    if (input->IsKeyboardKeyPressed(DIK_W))
    {
        actor_->Walk(velocity);
    } 
    if (input->IsKeyboardKeyPressed(DIK_S))
    {
        actor_->Walk(-velocity);
    }
    if (input->IsKeyboardKeyPressed(DIK_A))
    {
        actor_->Strafe(velocity);
    }
    if (input->IsKeyboardKeyPressed(DIK_D))
    {
        actor_->Strafe(-velocity);
    }
    if (input->IsKeyboardKeyPressed(DIK_Q))
    {
        actor_->TranslateXM(DirectX::XMVectorSet(0.0f, -velocity, 0.0f, 0.0f));
    }
    if (input->IsKeyboardKeyPressed(DIK_E))
    {
        actor_->TranslateXM(DirectX::XMVectorSet(0.0f, velocity, 0.0f, 0.0f));
    }

    int dx, dy;
    input->GetMouseDelta(dx, dy);
    FLOAT sensivity = 0.002f;
    actor_->Pitch(sensivity * FLOAT(-dy));
    actor_->RotateY(sensivity * FLOAT(dx));
}
