#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Object3D.h"

class Actor : public Object3D
{
public:
    Actor();
    virtual ~Actor();

    virtual VOID MoveTo(DirectX::XMVECTOR position);
    virtual VOID RotateTo(DirectX::XMVECTOR rotation);
    virtual VOID Move(DirectX::XMVECTOR offset);
    virtual VOID TurnAround(DirectX::XMVECTOR offset);
};

