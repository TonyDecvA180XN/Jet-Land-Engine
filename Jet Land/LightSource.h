#pragma once

#include "PoolObject.h"

namespace LightProperties
{
	enum LightType : INT32
	{
		LIGHT_TYPE_NONE  = 0,
		LIGHT_TYPE_SUN   = 1,
		LIGHT_TYPE_POINT = 2,
		LIGHT_TYPE_SPOT  = 3
	};
	enum LightFalloff : INT32
	{
		LIGHT_FALLOFF_DISABLED = 0,
		LIGHT_FALLOFF_LINEAR   = 1,
		LIGHT_FALLOFF_QUAD     = 2,
		LIGHT_FALLOFF_SPHERE   = 3
	};
}

class Light : public PoolObject
{
public:
	struct LightBuffer
	{

		DirectX::XMFLOAT4 color;                // 4*4=16 bytes
		DirectX::XMFLOAT3 position;             // 4*3=12 bytes
		FLOAT radius;                           // 4 bytes
		DirectX::XMFLOAT3 direction;            // 4*3=12 bytes
		FLOAT angle;                            // 4 bytes
		LightProperties::LightType type;        // 4 bytes
		LightProperties::LightFalloff falloff;  // 4 bytes
		DirectX::XMFLOAT2 _padding;             // (8) bytes
		//                                      Total: 56(64)
	};

	Light() : Light(LightProperties::LIGHT_TYPE_NONE) {};
	Light(LightProperties::LightType type);
	~Light() = default;

	LightProperties::LightType GetType();
	VOID SetType(LightProperties::LightType type);

	DirectX::XMVECTOR GetColorXM();
	VOID SetColorXM(DirectX::XMVECTOR color);
	VOID GetColor(FLOAT &r, FLOAT &g, FLOAT &b, FLOAT &a);
	VOID SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);

	DirectX::XMVECTOR GetPositionXM();
	VOID SetPositionXM(DirectX::XMVECTOR position);
	VOID GetPosition(FLOAT &x, FLOAT &y, FLOAT &z);
	VOID SetPosition(FLOAT x, FLOAT y, FLOAT z);

	DirectX::XMVECTOR GetDirectionXM();
	VOID SetDirectionXM(DirectX::XMVECTOR direction);
	VOID GetDirection(FLOAT &x, FLOAT &y, FLOAT &z);
	VOID SetDirection(FLOAT x, FLOAT y, FLOAT z);

	FLOAT GåtAngle();
	VOID SetAngle(FLOAT angle);

	LightBuffer GenerateBuffer();

private:

	LightProperties::LightType m_type;
	LightProperties::LightFalloff m_falloff;
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_direction;
	FLOAT m_angle;
	FLOAT m_radius;
};

