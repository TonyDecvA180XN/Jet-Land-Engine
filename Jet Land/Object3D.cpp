#include "Object3D.h"


Object3D::Object3D() : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f), scale_(1.0f, 1.0f, 1.0f)
{
}

Object3D::~Object3D()
= default;

DirectX::XMVECTOR Object3D::GetPosition()
{
    return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMVECTOR Object3D::GetRotation()
{
    return DirectX::XMLoadFloat3(&rotation_);
}

DirectX::XMVECTOR Object3D::GetScaling()
{
    return DirectX::XMLoadFloat3(&scale_);
}

VOID Object3D::SetPosition(DirectX::XMVECTOR position)
{
    DirectX::XMStoreFloat3(&position_, position);
}

VOID Object3D::SetRotation(DirectX::XMVECTOR rotation)
{
    DirectX::XMStoreFloat3(&rotation_, rotation);
}

VOID Object3D::SetScale(DirectX::XMVECTOR scale)
{
    DirectX::XMStoreFloat3(&scale_, scale);
}

DirectX::XMMATRIX Object3D::GetWorldMatrix()
{
    DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
    matrix *= DirectX::XMMatrixRotationRollPitchYaw(
        DirectX::XMConvertToRadians(rotation_.x),
        DirectX::XMConvertToRadians(rotation_.y),
        DirectX::XMConvertToRadians(rotation_.z)
    );
    matrix *= DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);
    matrix *= DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
    return matrix;
}
