#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Actor.h"
#include "Camera.h"

class PlayerActor : public Actor
{
public:
    PlayerActor();
    ~PlayerActor();

    VOID Update();

    Camera * GetCamera();
    VOID SetCamera(Camera * camera);

    VOID GetOffset(DirectX::XMVECTOR * pos, DirectX::XMVECTOR * rot);
    VOID SetOffset(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot);
private:
    Camera * camera_;
    DirectX::XMFLOAT3 camPosOffset_;
    DirectX::XMFLOAT3 camRotOffset_;
};

