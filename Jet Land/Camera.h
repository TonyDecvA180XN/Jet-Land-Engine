#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Object3D.h"

class Camera : public Object3D
{
public:
    Camera();
    ~Camera();

    VOID Create(FLOAT vertical_fov, UINT width, UINT height, FLOAT near_depth, FLOAT far_depth);
    VOID Frame();

    DirectX::XMMATRIX GetViewMatrix();
    DirectX::XMMATRIX GetProjMatrix();
    DirectX::XMMATRIX GetOrthoMatrix();

private:
    DirectX::XMMATRIX viewMatrix_;
    DirectX::XMMATRIX projMatrix_;
    DirectX::XMMATRIX orthoMatrix_;
};

