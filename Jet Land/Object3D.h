#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

class Object3D
{
public:
    Object3D();
    virtual ~Object3D();

    virtual DirectX::XMVECTOR GetPositionXM();
    virtual DirectX::XMVECTOR GetRotationXM();
    virtual DirectX::XMVECTOR GetScalingXM();

    virtual VOID GetPosition(FLOAT & x, FLOAT & y, FLOAT & z);
    virtual VOID GetRotation(FLOAT & x, FLOAT & y, FLOAT & z);
    virtual VOID GetScaling(FLOAT & x, FLOAT & y, FLOAT & z);

    virtual VOID SetPositionXM(DirectX::XMVECTOR position);
    virtual VOID SetRotationXM(DirectX::XMVECTOR rotation);
    virtual VOID SetScalingXM(DirectX::XMVECTOR scale);

    virtual VOID SetPosition(FLOAT x, FLOAT y, FLOAT z);
    virtual VOID SetRotation(FLOAT x, FLOAT y, FLOAT z);
    virtual VOID SetScaling(FLOAT x, FLOAT y, FLOAT z);

    virtual VOID TranslateXM(DirectX::XMVECTOR vector);
    virtual VOID Translate(FLOAT x, FLOAT y, FLOAT z);

    virtual VOID RotateXM(DirectX::XMVECTOR vector);
    virtual VOID Rotate(FLOAT x, FLOAT y, FLOAT z);

    virtual DirectX::XMMATRIX GetWorldMatrix();
protected:
    DirectX::XMFLOAT3 position_, rotation_, scale_;
};

