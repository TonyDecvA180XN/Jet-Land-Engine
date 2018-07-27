#include "LightSource.h"

DirectX::XMVECTOR LightSource::GetColor()
{
    return DirectX::XMLoadFloat4(&color_);
}

VOID LightSource::SetColor(DirectX::XMVECTOR color)
{
    DirectX::XMStoreFloat4(&color_, color);
}
