#include "LightSourceDirect.h"



LightSourceDirect::LightSourceDirect()
{
    direction_ = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
}


LightSourceDirect::~LightSourceDirect()
{
}

DirectX::XMVECTOR LightSourceDirect::GetDirection()
{
    return DirectX::XMLoadFloat3(&direction_);
}

VOID LightSourceDirect::SetDirection(DirectX::XMVECTOR direction)
{
    DirectX::XMStoreFloat3(&direction_, direction);
}
