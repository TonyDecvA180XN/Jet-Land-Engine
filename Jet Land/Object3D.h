#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

class Object3D
{
public:
    Object3D();
    virtual ~Object3D();

    virtual DirectX::XMVECTOR GetPosition();
    virtual DirectX::XMVECTOR GetRotation();
    virtual DirectX::XMVECTOR GetScaling();

    virtual VOID SetPosition(DirectX::XMVECTOR position);
    virtual VOID SetRotation(DirectX::XMVECTOR rotation);
    virtual VOID SetScale(DirectX::XMVECTOR scale);

    virtual DirectX::XMMATRIX GetWorldMatrix();
protected:
    DirectX::XMFLOAT3 position_, rotation_, scale_;
};

