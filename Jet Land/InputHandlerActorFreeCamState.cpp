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

	DirectX::XMFLOAT3 moveDirection(0.0f, 0.0f, 0.0f);
    if (input->IsKeyboardKeyPressed(DIK_LSHIFT))
    {
        velocity *= 4;
    } else if (input->IsKeyboardKeyPressed(DIK_LALT))
    {
        velocity /= 4;
    }
    if (input->IsKeyboardKeyPressed(DIK_W))
    {
		moveDirection.z += 1;
    } 
    if (input->IsKeyboardKeyPressed(DIK_S))
    {
		moveDirection.z -= 1;
    }
    if (input->IsKeyboardKeyPressed(DIK_A))
    {
		moveDirection.x -= 1;
    }
    if (input->IsKeyboardKeyPressed(DIK_D))
    {
		moveDirection.x += 1;
    }
    if (input->IsKeyboardKeyPressed(DIK_Q))
    {
		moveDirection.y -= 1;
    }
    if (input->IsKeyboardKeyPressed(DIK_E))
    {
		moveDirection.y += 1;
    }

	DirectX::XMVECTOR moveVector = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&moveDirection));
	moveVector = DirectX::XMVectorMultiply(moveVector, DirectX::XMVectorSet(velocity, velocity, velocity, 0.0f));
	//actor_->Move(moveVector);

    int dx, dy;
    input->GetMouseDelta(dx, dy);
    FLOAT sensivity = 0.002f;
	actor_->Look(sensivity * FLOAT(dx), sensivity * FLOAT(dy));
	actor_->Move(moveVector);
    /*actor_->Pitch();
    actor_->RotateY(sensivity * FLOAT(dx));*/
}
