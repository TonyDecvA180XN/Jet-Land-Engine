#include "ActorFreeCam.h"



ActorFreeCam::ActorFreeCam()
{
    camera_ = NULL;
    right_ = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
    up_ = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    look_ = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
}


ActorFreeCam::~ActorFreeCam()
{
}

VOID ActorFreeCam::Update(BOOL on_axis)
{
    camera_->SetPositionXM(this->GetPositionXM());
    camera_->SetRotationXM(this->GetRotationXM());
    if (on_axis)
    {
        Reorthonormalize();
        camera_->FrameOnAxes(GetBasisAxisLook(), GetBasisAxisUp());
    }
    else
    {
        camera_->FrameOnAngles();
    }
}

Camera * ActorFreeCam::GetCamera()
{
    return camera_;
}

VOID ActorFreeCam::SetCamera(Camera * camera)
{
    camera_ = camera;

}

DirectX::XMVECTOR ActorFreeCam::GetBasisAxisRight()
{
    return DirectX::XMLoadFloat3(&right_);
}

DirectX::XMVECTOR ActorFreeCam::GetBasisAxisUp()
{
    return DirectX::XMLoadFloat3(&up_);
}

DirectX::XMVECTOR ActorFreeCam::GetBasisAxisLook()
{
    return DirectX::XMLoadFloat3(&look_);
}

VOID ActorFreeCam::Walk(FLOAT distance)
{
    DirectX::XMVECTOR d = DirectX::XMVectorReplicate(distance);
    DirectX::XMVECTOR p = GetPositionXM();
    DirectX::XMVECTOR l = GetBasisAxisLook();
    // TODO : Change to MultiplyAdd
    DirectX::XMVECTOR s = DirectX::XMVectorMultiply(l, d);
    TranslateXM(s);
}

VOID ActorFreeCam::Strafe(FLOAT distance)
{
    DirectX::XMVECTOR d = DirectX::XMVectorReplicate(distance);
    DirectX::XMVECTOR p = GetPositionXM();
    DirectX::XMVECTOR r = GetBasisAxisRight();
    // TODO : Change to MultiplyAdd
    DirectX::XMVECTOR s = DirectX::XMVectorMultiply(r, d);
    TranslateXM(s);
}

VOID ActorFreeCam::Pitch(FLOAT angle)
{
    DirectX::XMMATRIX rm = DirectX::XMMatrixRotationAxis(GetBasisAxisRight(), angle);

    DirectX::XMStoreFloat3(&up_, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&up_), rm));
    DirectX::XMStoreFloat3(&look_, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&look_), rm));
}

VOID ActorFreeCam::RotateY(FLOAT angle)
{
    DirectX::XMMATRIX rm = DirectX::XMMatrixRotationY(angle);

    DirectX::XMStoreFloat3(&right_, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&right_), rm));
    DirectX::XMStoreFloat3(&up_, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&up_), rm));
    DirectX::XMStoreFloat3(&look_, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&look_), rm));
}

VOID ActorFreeCam::Reorthonormalize()
{
    DirectX::XMVECTOR r = GetBasisAxisRight();
    DirectX::XMVECTOR u = GetBasisAxisUp();
    DirectX::XMVECTOR l = GetBasisAxisLook();

    l = DirectX::XMVector3Normalize(l);
    u = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(l, r));
    r = DirectX::XMVector3Cross(u, l);
}
