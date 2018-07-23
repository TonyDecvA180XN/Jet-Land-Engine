#include "Camera.h"



Camera::Camera()
{
    viewMatrix_ = DirectX::XMMatrixIdentity();
    projMatrix_ = DirectX::XMMatrixIdentity();
    orthoMatrix_ = DirectX::XMMatrixIdentity();
}


Camera::~Camera()
=default;

VOID Camera::Create(FLOAT vertical_fov, UINT width, UINT height, FLOAT near_depth, FLOAT far_depth)
{
    projMatrix_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(vertical_fov), FLOAT(width) / FLOAT(height), near_depth, far_depth);
    orthoMatrix_ = DirectX::XMMatrixOrthographicLH(FLOAT(width), FLOAT(height), near_depth, far_depth);

}

VOID Camera::FrameOnAngles()
{
    DirectX::XMVECTOR eyePos, focusPos, upDir;

    eyePos = GetPositionXM();    
    focusPos = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    DirectX::XMMATRIX rotMatrix;
    rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation_.x), DirectX::XMConvertToRadians(rotation_.y), DirectX::XMConvertToRadians(rotation_.z));

    focusPos = DirectX::XMVector3TransformCoord(focusPos, rotMatrix);
    upDir = DirectX::XMVector3TransformCoord(upDir, rotMatrix);
    focusPos = DirectX::XMVectorAdd(focusPos, eyePos);
    viewMatrix_ = DirectX::XMMatrixLookAtLH(eyePos, focusPos, upDir);
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
    return viewMatrix_;
}

DirectX::XMMATRIX Camera::GetProjMatrix()
{
    return projMatrix_;
}

DirectX::XMMATRIX Camera::GetOrthoMatrix()
{
    return orthoMatrix_;
}

VOID Camera::FrameOnAxes(DirectX::XMVECTOR look_vector, DirectX::XMVECTOR up_vector)
{
    DirectX::XMVECTOR eyePos = GetPositionXM();
    DirectX::XMVECTOR focusPos = DirectX::XMVectorAdd(eyePos, look_vector);
    viewMatrix_ = DirectX::XMMatrixLookAtLH(eyePos, focusPos, up_vector);
}
