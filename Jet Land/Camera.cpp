#include "Camera.h"



Camera::Camera()
{
	viewMatrix_ = DirectX::XMMatrixIdentity();
	projMatrix_ = DirectX::XMMatrixIdentity();
	orthoMatrix_ = DirectX::XMMatrixIdentity();

	m_camPitch = 0.0f;
	m_camYaw = 0.0f;
	m_camGo = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
}


Camera::~Camera()
= default;

VOID Camera::Create(FLOAT vertical_fov, UINT width, UINT height, FLOAT near_depth, FLOAT far_depth)
{
	projMatrix_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(vertical_fov), FLOAT(width) / FLOAT(height), near_depth, far_depth);
	orthoMatrix_ = DirectX::XMMatrixOrthographicLH(FLOAT(width), FLOAT(height), near_depth, far_depth);

}

VOID Camera::FrameOnAngles()
{
	//DirectX::XMVECTOR eyePos = GetPositionXM();

	//DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation_.x),
	//	DirectX::XMConvertToRadians(rotation_.y),
	//	DirectX::XMConvertToRadians(rotation_.z));


	//m_lookVector = DirectX::XMVector3TransformCoord(m_vUnitZ, rotMatrix);
	////m_upVector = DirectX::XMVector3TransformCoord(m_vUnitY, rotMatrix);
	//m_rightVector = DirectX::XMVector3TransformCoord(m_vUnitX, rotMatrix);
	//DirectX::XMVECTOR lookAtVector = DirectX::XMVectorAdd(eyePos, m_lookVector);

	//viewMatrix_ = DirectX::XMMatrixLookAtLH(eyePos, lookAtVector, m_upVector);

	// this part of code is from DXUT framework but modified by me
 

	// Get keyboard/mouse/gamepad input
	//GetInput(m_bEnablePositionMovement, (m_nActiveButtonMask & m_nCurrentButtonMask) || m_bRotateWithoutButtonDown, true);

	//// Get the mouse movement (if any) if the mouse button are down
	//if( (m_nActiveButtonMask & m_nCurrentButtonMask) || m_bRotateWithoutButtonDown )
	//    UpdateMouseDelta( fElapsedTime );

	// Get amount of velocity based on the keyboard input and drag (if any)
	//UpdateVelocity(fElapsedTime);

	// Simple euler method to calculate position delta
	//XMVECTOR vVelocity = XMLoadFloat3(&m_vVelocity);
	//XMVECTOR vPosDelta = vVelocity * fElapsedTime;

	// If rotating the camera 
	//if ((m_nActiveButtonMask & m_nCurrentButtonMask)
	//	|| m_bRotateWithoutButtonDown
	//	|| m_vGamePadRightThumb.x != 0
	//	|| m_vGamePadRightThumb.z != 0)
	//{
	//	// Update the pitch & yaw angle based on mouse movement
	//	float fYawDelta = m_vRotVelocity.x;
	//	float fPitchDelta = m_vRotVelocity.y;

	//	// Invert pitch if requested
	//	if (m_bInvertPitch)
	//		fPitchDelta = -fPitchDelta;

	//	m_fCameraPitchAngle += fPitchDelta;
	//	m_fCameraYawAngle += fYawDelta;

	//	// Limit pitch to straight up or straight down
	//	m_fCameraPitchAngle = std::max(-XM_PI / 2.0f, m_fCameraPitchAngle);
	//	m_fCameraPitchAngle = std::min(+XM_PI / 2.0f, m_fCameraPitchAngle);
	//}

	// Make a rotation matrix based on the camera's yaw & pitch
	
	DirectX::XMMATRIX mCameraRot = DirectX::XMMatrixRotationRollPitchYaw(m_camPitch, m_camYaw, 0);

	// Transform vectors based on camera's rotation matrix
	DirectX::XMVECTOR vWorldUp = DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), mCameraRot);
	DirectX::XMVECTOR vWorldAhead = DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), mCameraRot);

	// Transform the position delta by the camera's rotation 
	//if (!m_bEnableYAxisMovement)
	//{
		// If restricting Y movement, do not include pitch
		// when transforming position delta vector.
	//	mCameraRot = XMMatrixRotationRollPitchYaw(0.0f, m_fCameraYawAngle, 0.0f);
	//}
	DirectX::XMFLOAT3 test;
	DirectX::XMStoreFloat3(&test, m_camGo);

	DirectX::XMVECTOR vPosDeltaWorld = DirectX::XMVector3TransformCoord(m_camGo, mCameraRot);
	
	// Move the eye position 
	DirectX::XMVECTOR vEye = this->GetPositionXM();
	vEye = DirectX::XMVectorAdd(vEye, vPosDeltaWorld);
	this->SetPositionXM(vEye);
	//if (m_bClipToBoundary)
	//	vEye = ConstrainToBoundary(vEye);

	// Update the lookAt position based on the eye position
	m_lookVector = DirectX::XMVectorAdd(vEye, vWorldAhead);
	//DirectX::XMStoreFloat4(&m_lookVector, vLookAt);

	// Update the view matrix
	viewMatrix_ = DirectX::XMMatrixLookAtLH(vEye, m_lookVector, vWorldUp);
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

VOID Camera::Rotate(FLOAT x, FLOAT y, FLOAT z)
{
	m_camPitch = DirectX::XMConvertToRadians(x);
	m_camYaw = DirectX::XMConvertToRadians(y);
}

VOID Camera::Look(FLOAT pitch, FLOAT yaw)
{
	m_camPitch += pitch;
	m_camPitch = max(-DirectX::XM_PIDIV2, m_camPitch);
	m_camPitch = min(DirectX::XM_PIDIV2, m_camPitch);
	m_camYaw += yaw;
}

VOID Camera::Move(DirectX::XMVECTOR move)
{
	m_camGo = move;
}
