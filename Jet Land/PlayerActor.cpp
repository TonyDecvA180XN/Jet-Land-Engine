#include "PlayerActor.h"



PlayerActor::PlayerActor()
{
    camera_ = NULL;
    camPosOffset_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    camRotOffset_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}


PlayerActor::~PlayerActor()
{
}

VOID PlayerActor::Update()
{
    camera_->SetPosition(DirectX::XMVectorAdd(this->GetPosition(), DirectX::XMLoadFloat3(&camPosOffset_)));
    camera_->SetRotation(DirectX::XMVectorAdd(this->GetRotation(), DirectX::XMLoadFloat3(&camRotOffset_)));
    camera_->Frame();
}

Camera * PlayerActor::GetCamera()
{
    return camera_;
}

VOID PlayerActor::SetCamera(Camera * camera)
{
    camera_ = camera;
}

VOID PlayerActor::GetOffset(DirectX::XMVECTOR * pos, DirectX::XMVECTOR * rot)
{
    *pos = DirectX::XMLoadFloat3(&camPosOffset_);
    *rot = DirectX::XMLoadFloat3(&camRotOffset_);
}

VOID PlayerActor::SetOffset(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot)
{
    DirectX::XMStoreFloat3(&camPosOffset_, pos);
    DirectX::XMStoreFloat3(&camRotOffset_, rot);
}
