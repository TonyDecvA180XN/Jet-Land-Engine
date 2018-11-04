#pragma once

#include "PoolObject.h"

class Material : public PoolObject 
{
public:
	struct MaterialBuffer
	{
		DirectX::XMFLOAT4 mDiffuse;
		DirectX::XMFLOAT4 mAmbient;
		DirectX::XMFLOAT4 mSpecular;
		FLOAT mRoughness;
		FLOAT mTransparency;
		FLOAT mMirror;
		FLOAT mIOR;
	};

	Material();
	~Material();

	DirectX::XMVECTOR GetDiffuseXM    ();
	VOID              SetDiffuseXM    (DirectX::XMVECTOR diffuse);
	VOID              GetDiffuse      (FLOAT &r, FLOAT &g, FLOAT &b);
	VOID              SetDiffuse      (FLOAT  r, FLOAT  g, FLOAT  b);

	DirectX::XMVECTOR GetAmbientXM    ();
	VOID              SetAmbientXM    (DirectX::XMVECTOR ambient);
	VOID              GetAmbient      (FLOAT &r, FLOAT &g, FLOAT &b);
	VOID              SetAmbient      (FLOAT r, FLOAT g, FLOAT b);

	DirectX::XMVECTOR GetSpecularXM   ();
	VOID              SetSpecularXM   (DirectX::XMVECTOR specular);
	VOID              GetSpecular     (FLOAT &r, FLOAT &g, FLOAT &b);
	VOID              SetSpecular     (FLOAT r, FLOAT g, FLOAT b);

	FLOAT             GåtRoughness    ();
	VOID              SetRoughness    (FLOAT roughness);

	FLOAT             GåtTransparency ();
	VOID              SetTransparency (FLOAT transparency);

	FLOAT             GåtMirror       ();
	VOID              SetMirror       (FLOAT mirror);

	FLOAT             GåtIOR          ();
	VOID              SetIOR          (FLOAT ior);

	MaterialBuffer GenerateBuffer();

private:
	friend class Loader;

	DirectX::XMFLOAT4 m_diffuse;
	DirectX::XMFLOAT4 m_ambient;
	DirectX::XMFLOAT4 m_specular;
	FLOAT m_roughness;
	FLOAT m_transparency;
	FLOAT m_mirror;
	FLOAT m_IOR;
};

