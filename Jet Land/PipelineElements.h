#pragma once

#include "Globals.h"
#include "VFormat.h"
#include "Pool.h"
#include "CompiledShader.h"
#include "LightCommonComponent.h"
#include "Material.h"
#include "Camera.h"
#include "Utils.h"
#include "Texture.h"
#include "TransformationBuffer.h"

class PipelineElements
{
public:
	struct AuxiliaryBuffer
	{
		DirectX::XMFLOAT4 eyePos;
	};

public:
	PipelineElements();
	~PipelineElements();

	VOID Initiate(ID3D11Device * device, LightCommonComponent * lights);
	VOID Destroy();

	VOID SetVSandIL(ID3D11Device * device, CompiledShader * vs, VFORMAT format);
	VOID SetPS(ID3D11Device * device, CompiledShader * ps);
	VOID SetGeometry(ID3D11Device * device, VOID * vertices_data, UINT vertices_size, UINT * indices_data, UINT index_count);
	VOID SetTransformation(ID3D11DeviceContext * device_context, TransformationBuffer tb);
	VOID SetMaterial(ID3D11DeviceContext * device_context, Material::MaterialBuffer mb);
	VOID SetTexture(Texture * texture);

	VOID Draw(ID3D11DeviceContext * device_context, Camera * camera, UINT index_count, UINT vertex_size);

private:
	ID3D11InputLayout * m_il;
	ID3D11VertexShader * m_vs;
	ID3D11PixelShader * m_ps;
	ID3D11SamplerState * m_ss;
	ID3D11ShaderResourceView * m_tex;
	ID3D11Buffer * m_vb, * m_ib;
	ID3D11Buffer * m_tb;
	ID3D11Buffer * m_mb;
	ID3D11Buffer * m_auxb;
	LightCommonComponent * m_lightComponent;
};

