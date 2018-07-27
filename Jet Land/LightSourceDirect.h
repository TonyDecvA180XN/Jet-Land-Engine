#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

#include "LightSource.h"

class LightSourceDirect :
    public LightSource
{
public:
    LightSourceDirect();
    ~LightSourceDirect();

    DirectX::XMVECTOR GetDirection();
    VOID SetDirection(DirectX::XMVECTOR direction);

private:
    DirectX::XMFLOAT3 direction_;
};

