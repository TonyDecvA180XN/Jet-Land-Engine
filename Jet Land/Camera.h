#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

class Camera
{
public:
    Camera();
    ~Camera();

    VOID Create(FLOAT vertical_fov, UINT width, UINT height, FLOAT near_depth, FLOAT far_depth);
    VOID Frame();

    DirectX::XMMATRIX GetViewMatrix();
    DirectX::XMMATRIX GetProjMatrix();
    DirectX::XMMATRIX GetOrthoMatrix();

    DirectX::XMVECTOR GetPosition();
    DirectX::XMVECTOR GetRotation();
    VOID SetPosition(FLOAT x, FLOAT y, FLOAT z);
    VOID SetRotation(FLOAT x, FLOAT y, FLOAT z);

private:
    DirectX::XMMATRIX viewMatrix_;
    DirectX::XMMATRIX projMatrix_;
    DirectX::XMMATRIX orthoMatrix_;
    DirectX::XMFLOAT3 position_;
    DirectX::XMFLOAT3 rotation_; // in degrees
};

