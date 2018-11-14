#include "PipelineElements.h"

PipelineElements::PipelineElements() :
	m_il(NULL),
	m_vs(NULL),
	m_ps(NULL),
	m_ss(NULL),
	m_vb(NULL),
	m_ib(NULL),
	m_tb(NULL),
	m_mb(NULL),
	m_lightComponent(NULL)
{}

PipelineElements::~PipelineElements()
= default;

VOID PipelineElements::Initiate(ID3D11Device * device, LightCommonComponent * lights)
{
	m_lightComponent = lights;
	// ------------------- Creating Transformation Buffer ---------------------
	D3D11_BUFFER_DESC tbDescription;
	tbDescription.Usage = D3D11_USAGE_DYNAMIC; // may updates after creating
	tbDescription.ByteWidth = sizeof TransformationBuffer; // size of matrices buffer
	tbDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // GPU cannot write
	tbDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU can write
	tbDescription.MiscFlags = 0; // bullshit
	tbDescription.StructureByteStride = 0; // bullshit

	device->CreateBuffer(&tbDescription, NULL, &m_tb);

	// ------------------- Creating Material Buffer ---------------------------
	D3D11_BUFFER_DESC mbDescription;
	mbDescription.Usage = D3D11_USAGE_DYNAMIC; // may updates after creating
	mbDescription.ByteWidth = sizeof Material::MaterialBuffer; // size of material buffer
	mbDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // GPU cannot write
	mbDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU can write
	mbDescription.MiscFlags = 0; // bullshit
	mbDescription.StructureByteStride = 0; // bullshit

	device->CreateBuffer(&mbDescription, NULL, &m_mb);

	// ------------------- Creating Auxiliary Buffer --------------------------
	D3D11_BUFFER_DESC abDescription;
	abDescription.Usage = D3D11_USAGE_DYNAMIC; // may updates after creating
	abDescription.ByteWidth = sizeof PipelineElements::AuxiliaryBuffer; // size of auxiliary buffer
	abDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // GPU cannot write
	abDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU can write
	abDescription.MiscFlags = 0; // bullshit
	abDescription.StructureByteStride = 0; // bullshit

	device->CreateBuffer(&abDescription, NULL, &m_auxb);


	// ------------------- Creating Sampler State -----------------------------
	D3D11_SAMPLER_DESC ssDescription;
	ssDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	ssDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	ssDescription.MipLODBias = 0.0f;
	ssDescription.MaxAnisotropy = 1;
	ssDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	ssDescription.BorderColor[0] = 0;
	ssDescription.BorderColor[1] = 0;
	ssDescription.BorderColor[2] = 0;
	ssDescription.BorderColor[3] = 0;
	ssDescription.MinLOD = 0;
	ssDescription.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&ssDescription, &m_ss);
}

VOID PipelineElements::Destroy()
{
	ReleaseCOM(m_il);
	ReleaseCOM(m_vs);
	ReleaseCOM(m_ps);
	ReleaseCOM(m_ss);
	ReleaseCOM(m_vb);
	ReleaseCOM(m_ib);
	ReleaseCOM(m_tb);
	ReleaseCOM(m_mb);
}

VOID PipelineElements::SetVSandIL(ID3D11Device * device, CompiledShader * vs, VFORMAT format)
{
	ReleaseCOM(m_vs);
	ReleaseCOM(m_il);

	UINT inputElementCount = 0;
	D3D11_INPUT_ELEMENT_DESC * descriptions = new D3D11_INPUT_ELEMENT_DESC[5];

	if (format & PositionMask)
	{
		descriptions[inputElementCount].SemanticName = "POSITION";
		descriptions[inputElementCount].SemanticIndex = 0;
		descriptions[inputElementCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		descriptions[inputElementCount].InputSlot = 0;
		descriptions[inputElementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[inputElementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[inputElementCount].InstanceDataStepRate = 0;
		inputElementCount++;
	}
	if (format & ColorMask)
	{
		descriptions[inputElementCount].SemanticName = "VERTEXCOLOR";
		descriptions[inputElementCount].SemanticIndex = 0;
		descriptions[inputElementCount].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		descriptions[inputElementCount].InputSlot = 0;
		descriptions[inputElementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[inputElementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[inputElementCount].InstanceDataStepRate = 0;
		inputElementCount++;
	}
	if (format & TexcoordsMask)
	{
		descriptions[inputElementCount].SemanticName = "TEXCOORDS";
		descriptions[inputElementCount].SemanticIndex = 0;
		descriptions[inputElementCount].Format = DXGI_FORMAT_R32G32_FLOAT;
		descriptions[inputElementCount].InputSlot = 0;
		descriptions[inputElementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[inputElementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[inputElementCount].InstanceDataStepRate = 0;
		inputElementCount++;
	}
	if (format & NormalsMask)
	{
		descriptions[inputElementCount].SemanticName = "NORMAL";
		descriptions[inputElementCount].SemanticIndex = 0;
		descriptions[inputElementCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		descriptions[inputElementCount].InputSlot = 0;
		descriptions[inputElementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[inputElementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[inputElementCount].InstanceDataStepRate = 0;
		inputElementCount++;
	}

	device->CreateVertexShader(vs->Get(), vs->GetSize(), NULL, &m_vs);
	device->CreateInputLayout(descriptions, inputElementCount, vs->Get(), vs->GetSize(), &m_il);
}

VOID PipelineElements::SetPS(ID3D11Device * device, CompiledShader * ps)
{
	ReleaseCOM(m_ps);
	device->CreatePixelShader(ps->Get(), ps->GetSize(), NULL, &m_ps);
}

VOID PipelineElements::SetGeometry(ID3D11Device * device, VOID * vertices_data, UINT vertices_size, UINT * indices_data, UINT index_count)
{
	ReleaseCOM(m_vb);
	ReleaseCOM(m_ib);

	D3D11_BUFFER_DESC vbDescription;
	vbDescription.Usage = D3D11_USAGE_IMMUTABLE; // data in static mesh won't be changed
	vbDescription.ByteWidth = vertices_size; // size of vertex buffer
	vbDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; // GPU only reads it on pipeline
	vbDescription.CPUAccessFlags = 0; // CPU cannot write
	vbDescription.MiscFlags = 0; // bullshit
	vbDescription.StructureByteStride = 0; // bullshit

	D3D11_SUBRESOURCE_DATA vbInitial;
	vbInitial.pSysMem = vertices_data;
	vbInitial.SysMemPitch = 0;
	vbInitial.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC ibDescription;
	ibDescription.Usage = D3D11_USAGE_IMMUTABLE; // data in static mesh won't be changed
	ibDescription.ByteWidth = index_count * sizeof UINT; // size of index buffer
	ibDescription.BindFlags = D3D11_BIND_INDEX_BUFFER; // GPU only reads it on pipeline
	ibDescription.CPUAccessFlags = 0; // CPU cannot write
	ibDescription.MiscFlags = 0; // bullshit
	ibDescription.StructureByteStride = 0; // bullshit

	D3D11_SUBRESOURCE_DATA ibInitial;
	ibInitial.pSysMem = indices_data;
	ibInitial.SysMemPitch = 0;
	ibInitial.SysMemSlicePitch = 0;

	device->CreateBuffer(&vbDescription, &vbInitial, &m_vb);
	device->CreateBuffer(&ibDescription, &ibInitial, &m_ib);
}

VOID PipelineElements::SetTransformation(ID3D11DeviceContext * device_context, TransformationBuffer tb)
{
	// transpose matrices because it's requirement of DirectX 11
	tb.m_world = DirectX::XMMatrixTranspose(tb.m_world);
	tb.m_view = DirectX::XMMatrixTranspose(tb.m_view);
	tb.m_projection = DirectX::XMMatrixTranspose(tb.m_projection);

	D3D11_MAPPED_SUBRESOURCE resource;
	device_context->Map(m_tb, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	auto inside_data = (TransformationBuffer *)(resource.pData);
	inside_data->m_world = tb.m_world;
	inside_data->m_view = tb.m_view;
	inside_data->m_projection = tb.m_projection;

	device_context->Unmap(m_tb, 0);
}

VOID PipelineElements::SetMaterial(ID3D11DeviceContext * device_context, Material::MaterialBuffer mb)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = device_context->Map(m_mb, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	auto inside_data = (Material::MaterialBuffer *)(resource.pData);
	inside_data->mDiffuse = mb.mDiffuse;
	inside_data->mAmbient = mb.mAmbient;
	inside_data->mSpecular = mb.mSpecular;
	inside_data->mShininess = mb.mShininess;
	inside_data->mTransparency = mb.mTransparency;
	inside_data->mMirror = mb.mMirror;
	inside_data->mIOR = mb.mIOR;

	device_context->Unmap(m_mb, 0);
}

VOID PipelineElements::SetTexture(Texture * texture)
{
	m_tex = texture->Get();
}

VOID PipelineElements::Draw(ID3D11DeviceContext * device_context, Camera * camera, UINT index_count, UINT vertex_size)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = device_context->Map(m_auxb, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	auto inside_data = (PipelineElements::AuxiliaryBuffer *)(resource.pData);
	DirectX::XMStoreFloat4(&inside_data->eyePos, camera->GetPositionXM());

	device_context->Unmap(m_auxb, 0);

	UINT stride = vertex_size, offset = 0;
	device_context->IASetInputLayout(m_il);
	device_context->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	device_context->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	device_context->VSSetShader(m_vs, NULL, 0);
	device_context->VSSetConstantBuffers(0, 1, &m_tb);
	device_context->PSSetShader(m_ps, NULL, 0);
	device_context->PSSetConstantBuffers(0, 1, m_lightComponent->GetBufferLP());
	device_context->PSSetConstantBuffers(1, 1, &m_mb);
	device_context->PSSetConstantBuffers(2, 1, &m_auxb);

	// !!! there the NULL textures also bind to pipeline, so samplers return 0,
	// but if limit this by condition, the srv will be used from previous draw call !!!
		device_context->PSSetSamplers(0, 1, &m_ss);
		device_context->PSSetShaderResources(0, 1, &m_tex);

	// final draw call
	device_context->DrawIndexed(index_count, 0, 0);
}
