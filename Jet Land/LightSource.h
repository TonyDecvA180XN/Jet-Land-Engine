#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

class LightSource
{
public:
    LightSource() = default;
    virtual ~LightSource() = default;

    DirectX::XMVECTOR GetColor();
    VOID SetColor(DirectX::XMVECTOR color);

private:
    DirectX::XMFLOAT4 color_;
};

