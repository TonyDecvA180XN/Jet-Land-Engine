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
		FLOAT mShininess;
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

	FLOAT             G�tShininess    ();
	VOID              SetShininess    (FLOAT shininess);

	FLOAT             G�tTransparency ();
	VOID              SetTransparency (FLOAT transparency);

	FLOAT             G�tMirror       ();
	VOID              SetMirror       (FLOAT mirror);

	FLOAT             G�tIOR          ();
	VOID              SetIOR          (FLOAT ior);

	MaterialBuffer GenerateBuffer();

private:
	friend class Loader;

	DirectX::XMFLOAT4 m_diffuse;
	DirectX::XMFLOAT4 m_ambient;
	DirectX::XMFLOAT4 m_specular;
	FLOAT m_shininess;
	FLOAT m_transparency;
	FLOAT m_mirror;
	FLOAT m_IOR;
};

