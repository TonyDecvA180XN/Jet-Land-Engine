#pragma once



#include "Object3D.h"

class Camera : public Object3D
{
public:
    Camera();
    ~Camera();

    VOID Create(FLOAT vertical_fov, UINT width, UINT height, FLOAT near_depth, FLOAT far_depth);
    VOID FrameOnAngles();

	VOID Look(FLOAT pitch, FLOAT yaw);
	VOID Move(DirectX::XMVECTOR move);

    DirectX::XMMATRIX GetViewMatrix();
    DirectX::XMMATRIX GetProjMatrix();
    DirectX::XMMATRIX GetOrthoMatrix();    

	VOID Rotate(FLOAT x, FLOAT y, FLOAT z) override;

	// mfd
	/*DirectX::XMVECTOR GetLookVector();
	DirectX::XMVECTOR GetUpVector();
	DirectX::XMVECTOR GetRightVector();*/

private:
	FLOAT m_camPitch, m_camYaw;
	DirectX::XMVECTOR m_camGo;

	DirectX::XMVECTOR m_lookVector, m_upVector, m_rightVector;

    DirectX::XMMATRIX viewMatrix_;
    DirectX::XMMATRIX projMatrix_;
    DirectX::XMMATRIX orthoMatrix_;
};

