#include "LightSource.h"

Light::Light(LightProperties::LightType type) :
	m_type(type),
	m_falloff(LightProperties::LIGHT_FALLOFF_DISABLED),
	m_color(1.0f, 1.0f, 1.0f, 1.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_direction(0.0f, -1.0f, 0.0f),
	m_angle(45.0f),
	m_radius(100.0f)
{
}

DirectX::XMVECTOR Light::GetColorXM()
{
	return DirectX::XMLoadFloat4(&m_color);
}

VOID Light::SetColorXM(DirectX::XMVECTOR color)
{
	DirectX::XMStoreFloat4(&m_color, color);
}

VOID Light::GetColor(FLOAT & r, FLOAT & g, FLOAT & b, FLOAT & a)
{
	r = m_color.x;
	g = m_color.y;
	b = m_color.z;
	a = m_color.w;
}

VOID Light::SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
	m_color.w = a;
}

DirectX::XMVECTOR Light::GetPositionXM()
{
	return DirectX::XMLoadFloat3(&m_position);
}

VOID Light::SetPositionXM(DirectX::XMVECTOR position)
{
	DirectX::XMStoreFloat3(&m_position, position);
}

VOID Light::GetPosition(FLOAT & x, FLOAT & y, FLOAT & z)
{
	x = m_position.x;
	y = m_position.y;
	z = m_position.z;
}

VOID Light::SetPosition(FLOAT x, FLOAT y, FLOAT z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

DirectX::XMVECTOR Light::GetDirectionXM()
{
	return DirectX::XMLoadFloat3(&m_direction);
}

VOID Light::SetDirectionXM(DirectX::XMVECTOR direction)
{
	DirectX::XMStoreFloat3(&m_direction, direction);
}

VOID Light::GetDirection(FLOAT & x, FLOAT & y, FLOAT & z)
{
	x = m_direction.x;
	y = m_direction.y;
	z = m_direction.z;
}

VOID Light::SetDirection(FLOAT x, FLOAT y, FLOAT z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
}

FLOAT Light::GåtAngle()
{
	return m_angle;
}

VOID Light::SetAngle(FLOAT angle)
{
	m_angle = angle;
}

Light::LightBuffer Light::GenerateBuffer()
{
	Light::LightBuffer buffer;
	buffer.type = m_type;
	buffer.falloff = m_falloff;
	buffer.position = m_position;
	buffer.direction = m_direction;
	buffer.color = m_color;
	buffer.angle = m_angle;
	buffer.radius = m_radius;
	return buffer;
}
