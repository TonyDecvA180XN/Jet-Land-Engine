#include "Object3D.h"


Object3D::Object3D() : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f), scale_(1.0f, 1.0f, 1.0f)
{
}

Object3D::~Object3D()
= default;

DirectX::XMVECTOR Object3D::GetPositionXM()
{
	return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMVECTOR Object3D::GetRotationXM()
{
	return DirectX::XMLoadFloat3(&rotation_);
}

DirectX::XMVECTOR Object3D::GetScalingXM()
{
	return DirectX::XMLoadFloat3(&scale_);
}

VOID Object3D::GetPosition(FLOAT & x, FLOAT & y, FLOAT & z)
{
	x = position_.x;
	y = position_.y;
	z = position_.z;
}

VOID Object3D::GetRotation(FLOAT & x, FLOAT & y, FLOAT & z)
{
	x = rotation_.x;
	y = rotation_.y;
	z = rotation_.z;
}

VOID Object3D::GetScaling(FLOAT & x, FLOAT & y, FLOAT & z)
{
	x = scale_.x;
	y = scale_.y;
	z = scale_.z;
}

VOID Object3D::SetPositionXM(DirectX::XMVECTOR position)
{
	DirectX::XMStoreFloat3(&position_, position);
}

VOID Object3D::SetRotationXM(DirectX::XMVECTOR rotation)
{
	DirectX::XMStoreFloat3(&rotation_, rotation);
}

VOID Object3D::SetScalingXM(DirectX::XMVECTOR scale)
{
	DirectX::XMStoreFloat3(&scale_, scale);
}

VOID Object3D::SetPosition(FLOAT x, FLOAT y, FLOAT z)
{
	position_.x = x;
	position_.y = y;
	position_.z = z;
}

VOID Object3D::SetRotation(FLOAT x, FLOAT y, FLOAT z)
{
	rotation_.x = x;
	rotation_.y = y;
	rotation_.z = z;
}

VOID Object3D::SetScaling(FLOAT x, FLOAT y, FLOAT z)
{
	scale_.x = x;
	scale_.y = y;
	scale_.z = z;
}

VOID Object3D::TranslateXM(DirectX::XMVECTOR vector)
{
	DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), vector));
}

VOID Object3D::Translate(FLOAT x, FLOAT y, FLOAT z)
{
	position_.x += x;
	position_.y += y;
	position_.z += z;
}

VOID Object3D::RotateXM(DirectX::XMVECTOR vector)
{
	DirectX::XMStoreFloat3(&rotation_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&rotation_), vector));
}

VOID Object3D::Rotate(FLOAT x, FLOAT y, FLOAT z)
{
	rotation_.x += x;
	rotation_.y += y;
	rotation_.z += z;
}

DirectX::XMMATRIX Object3D::GetWorldMatrix()
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
	matrix *= DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matrix *= DirectX::XMMatrixRotationRollPitchYaw(
		DirectX::XMConvertToRadians(rotation_.x),
		DirectX::XMConvertToRadians(rotation_.y),
		DirectX::XMConvertToRadians(rotation_.z)
	);
	matrix *= DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);

	return matrix;
}
