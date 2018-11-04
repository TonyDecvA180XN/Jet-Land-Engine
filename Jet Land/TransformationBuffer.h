#pragma once

struct TransformationBuffer
{
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
};