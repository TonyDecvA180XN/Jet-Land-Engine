#include "Actor.h"



Actor::Actor()
{
}


Actor::~Actor()
= default;

VOID Actor::MoveTo(DirectX::XMVECTOR position)
{
    this->SetPosition(position);
}

VOID Actor::RotateTo(DirectX::XMVECTOR rotation)
{
    this->SetRotation(rotation);
}

VOID Actor::Move(DirectX::XMVECTOR offset)
{
    this->SetPosition(DirectX::XMVectorAdd(this->GetPosition(), offset));
}

VOID Actor::TurnAround(DirectX::XMVECTOR offset)
{
    this->SetRotation(DirectX::XMVectorAdd(this->GetRotation(), offset));
}
