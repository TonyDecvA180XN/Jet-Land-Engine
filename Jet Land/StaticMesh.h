#pragma once

#include "Object3D.h"
#include "PoolObject.h"
#include "Utils.h"
#include "Mesh.h"
#include "Material.h"
#include "LightCommonComponent.h"
#include "Camera.h"
#include "PipelineElements.h"
#include "Texture.h"
#include "CompiledShader.h"
#include "TransformationBuffer.h"

class StaticMesh : public Object3D, public PoolObject
{
public:
	StaticMesh();
	~StaticMesh();
	
	VOID Initiate(
		ID3D11Device * device,
		ID3D11DeviceContext * device_context,
		LightCommonComponent * lights,
		Camera * camera,
		Mesh * mesh,
		Material * material,
		Texture * texture,
		CompiledShader * vs,
		CompiledShader * ps);

	VOID Terminate() override;

	VOID Render(ID3D11DeviceContext * device_context);

	Mesh * GetMesh();
	Material * GetMaterial();
	Texture * GetTexture();

private:
	Mesh * m_mesh;
	Material * m_material;
	Texture * m_texture;
	PipelineElements * m_pe;
	CompiledShader * m_vs, * m_ps;
	TransformationBuffer m_tb;

	Camera * m_cam;
};

