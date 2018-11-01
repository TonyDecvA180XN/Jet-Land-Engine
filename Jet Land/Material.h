#pragma once

#include "Globals.h"
#include "LightSource.h"
#include "Pool.h"
#include "PoolObject.h"

#include "VFormat.h"


class Material : public PoolObject 
{
public:
	Material() :
		Material(
			"default",
			DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f),
			FLOAT(1.0f),
			FLOAT(0.0f),
			FLOAT(0.0f),
			FLOAT(1.45f)
		) {};
	Material(
		std::string name,
		DirectX::XMFLOAT4 diffuse,
		DirectX::XMFLOAT4 ambient,
		DirectX::XMFLOAT4 specular,
		FLOAT roughness,
		FLOAT transparency,
		FLOAT mirror,
		FLOAT IOR
	) :
		PoolObject(name),
		m_diffuse(diffuse),
		m_ambient(ambient),
		m_specular(specular),
		m_roughness(roughness),
		m_transparency(transparency),
		m_mirror(mirror),
		m_IOR(IOR),

		vs_(NULL),
		ps_(NULL),
		il_(NULL),
		transformMatrixBuffer_(NULL),
		lightBuffer_(NULL),
		sampler_(NULL)
	{}
	~Material();

	BOOL LoadVertexShaderAndInputLayout(ID3D11Device * device, LPSTR filename, VFORMAT vertex_format);
	BOOL LoadPixelShader(ID3D11Device * device, LPSTR filename);

	BOOL CreateTransformMatrixBuffer(ID3D11Device * device);
	BOOL UpdateTransformation(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix);

	BOOL CreateLightBuffer(ID3D11Device * device);
	BOOL UpdateLight(ID3D11DeviceContext * device_context, Pool<Light> * lights);

	BOOL CreateMaterialBuffer(ID3D11Device * device);
	BOOL UpdateMaterialBuffer(ID3D11DeviceContext * device_context);

	VOID DrawObject(ID3D11DeviceContext * device_context, UINT index_count, ID3D11ShaderResourceView * srv);

	VOID Destroy();

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

private:
	struct TransformMatrixBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

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

private:
	DirectX::XMFLOAT4 m_diffuse;
	DirectX::XMFLOAT4 m_ambient;
	DirectX::XMFLOAT4 m_specular;
	FLOAT m_roughness;
	FLOAT m_transparency;
	FLOAT m_mirror;
	FLOAT m_IOR;

	ID3D11VertexShader * vs_;
	ID3D11PixelShader * ps_;
	ID3D11InputLayout * il_;
	ID3D11Buffer * transformMatrixBuffer_;
	ID3D11Buffer * lightBuffer_;
	ID3D11Buffer * m_materialBuffer;
	ID3D11SamplerState * sampler_;
};

