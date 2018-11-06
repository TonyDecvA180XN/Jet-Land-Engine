#include "StaticMesh.h"


StaticMesh::StaticMesh() :
	m_mesh(NULL),
	m_material(NULL),
	m_pe(NULL),
	m_vs(NULL),
	m_ps(NULL),
	m_texture(NULL),
	m_cam(NULL)
{}

StaticMesh::~StaticMesh()
= default;

VOID StaticMesh::Initiate(
	ID3D11Device * device,
	ID3D11DeviceContext * device_context,
	LightCommonComponent * lights,
	Camera * camera,
	Mesh * mesh,
	Material * material,
	Texture * texture,
	CompiledShader * vs,
	CompiledShader * ps)
{
	m_mesh = mesh;
	m_material = material;
	m_texture = texture;
	m_vs = vs;
	m_ps = ps;
	m_cam = camera;

	m_pe = new PipelineElements;
	CheckAllocation(m_pe);

	m_pe->Initiate(device, lights);
	m_pe->SetVSandIL(device, vs, m_mesh->GetVertexFormat());
	m_pe->SetPS(device, ps);
	m_pe->SetGeometry(device, m_mesh->GetVertices(), m_mesh->GetVertexSize() * m_mesh->GetVertexCount(), m_mesh->GetIndices(), m_mesh->GetIndexCount());
	m_pe->SetTransformation(device_context, m_tb);
	m_pe->SetMaterial(device_context, material->GenerateBuffer());
	if (texture != NULL)
	{
		m_pe->SetTexture(texture);
	}
}

VOID StaticMesh::Terminate()
{
	m_pe->Destroy();
	PoolObject::Terminate();
}

VOID StaticMesh::Render(ID3D11DeviceContext * device_context)
{
	ID3D11Device * device;
	device_context->GetDevice(&device);
	if (m_mesh->CheckForUpdates())
	{
		m_pe->SetGeometry(device, m_mesh->GetVertices(), m_mesh->GetVertexSize() * m_mesh->GetVertexCount(), m_mesh->GetIndices(), m_mesh->GetVertexCount());
	}

	m_tb.m_world = this->GetWorldMatrix();
	m_tb.m_view = m_cam->GetViewMatrix();
	m_tb.m_projection = m_cam->GetProjMatrix();
	m_pe->SetTransformation(device_context, m_tb);
	if (m_material->CheckForUpdates())
	{
		m_pe->SetMaterial(device_context, m_material->GenerateBuffer());
	}
	if (m_texture && m_texture->CheckForUpdates())
	{
		m_pe->SetTexture(m_texture);
	}

	m_pe->Draw(device_context, this->m_cam, m_mesh->GetIndexCount(), m_mesh->GetVertexSize());
}

Mesh * StaticMesh::GetMesh()
{
	return m_mesh;
}

Material * StaticMesh::GetMaterial()
{
	return m_material;
}

Texture * StaticMesh::GetTexture()
{
	return m_texture;
}
