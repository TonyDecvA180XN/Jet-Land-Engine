#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Actor.h"
#include "Camera.h"

class ActorFreeCam : public Actor
{
public:
    ActorFreeCam();
    ~ActorFreeCam();

    VOID Update(BOOL on_axis);

    Camera * GetCamera();
    VOID SetCamera(Camera * camera);

    DirectX::XMVECTOR GetBasisAxisRight();
    DirectX::XMVECTOR GetBasisAxisUp();
    DirectX::XMVECTOR GetBasisAxisLook();

    VOID Walk(FLOAT distance);
    VOID Strafe(FLOAT distance);

    VOID Pitch(FLOAT angle);
    VOID RotateY(FLOAT angle);

private:
    VOID Reorthonormalize();

private:
    Camera * camera_;
    DirectX::XMFLOAT3 right_, up_, look_;
};

