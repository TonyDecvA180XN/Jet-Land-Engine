#include "Material.h"

std::ifstream::pos_type filesize(LPSTR filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

Material::~Material()
= default;

BOOL Material::LoadVertexShaderAndInputLayout(ID3D11Device * device, LPSTR filename, VFORMAT vertex_format)
{
	HRESULT result;

	size_t size = filesize(filename);
	std::ifstream input(filename, std::ifstream::binary | std::istream::in);
	if (input.fail()) { return FALSE; }
	uint8_t * ptr = new uint8_t[size];
	input.read((char *)(ptr), size);
	input.close();
	/*
	ID3D10Blob * shaderBuffer;
	ID3D10Blob * errors;
	result = D3DCompileFromFile(filename, NULL, NULL, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBuffer, &errors);
	if (result == ERROR_FILE_NOT_FOUND)
	{
		std::wstring err;
		err += L"Error opening shader source file\n";
		err += L"Cannot find file \"";
		err += filename;
		err += L"\".\n\n";
		CrashManager::CrashLog(L"crash.txt", err);
		return FALSE;
	}
	else if (FAILED(result))
	{
		if (errors)
		{
			CrashManager::CrashLog(L"crash.txt", errors);
		}
		return FALSE;
	}

	result = device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &vs_);
	if (FAILED(result)) { return FALSE; }
	*/
	UINT ilElementsCount = 0;
	D3D11_INPUT_ELEMENT_DESC * descriptions = new D3D11_INPUT_ELEMENT_DESC[5];
	if (!descriptions) { return FALSE; }

	if (vertex_format & PositionMask)
	{
		descriptions[ilElementsCount].SemanticName = "POSITION";
		descriptions[ilElementsCount].SemanticIndex = 0;
		descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		descriptions[ilElementsCount].InputSlot = 0;
		descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[ilElementsCount].InstanceDataStepRate = 0;
		ilElementsCount++;
	}

	if (vertex_format & ColorMask)
	{
		descriptions[ilElementsCount].SemanticName = "VERTEXCOLOR";
		descriptions[ilElementsCount].SemanticIndex = 0;
		descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		descriptions[ilElementsCount].InputSlot = 0;
		descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[ilElementsCount].InstanceDataStepRate = 0;
		ilElementsCount++;
	}

	if (vertex_format & TexcoordsMask)
	{
		descriptions[ilElementsCount].SemanticName = "TEXCOORDS";
		descriptions[ilElementsCount].SemanticIndex = 0;
		descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32_FLOAT;
		descriptions[ilElementsCount].InputSlot = 0;
		descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[ilElementsCount].InstanceDataStepRate = 0;
		ilElementsCount++;
	}

	if (vertex_format & NormalsMask)
	{
		descriptions[ilElementsCount].SemanticName = "NORMAL";
		descriptions[ilElementsCount].SemanticIndex = 0;
		descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		descriptions[ilElementsCount].InputSlot = 0;
		descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		descriptions[ilElementsCount].InstanceDataStepRate = 0;
		ilElementsCount++;
	}


	result = device->CreateVertexShader(ptr, size, NULL, &vs_);
	if (FAILED(result)) { return FALSE; }

	result = device->CreateInputLayout(descriptions, ilElementsCount, ptr, size, &il_);
	if (FAILED(result)) { return FALSE; }

	/*
	shaderBuffer->Release();
	shaderBuffer = NULL;
	*/




	//delete[] descriptions;

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &sampler_);
	if (FAILED(result))
	{
		return false;
	}

	return TRUE;
}

BOOL Material::LoadPixelShader(ID3D11Device * device, LPSTR filename)
{
	HRESULT result;
	/*
	ID3D10Blob * shaderBuffer;
	ID3D10Blob * errors;
	result = D3DCompileFromFile(filename, NULL, NULL, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBuffer, &errors);
	if (result == ERROR_FILE_NOT_FOUND)
	{
		std::wstring err;
		err += L"Error opening shader source file\n";
		err += L"Cannot find file \"";
		err += filename;
		err += L"\".\n\n";
		CrashManager::CrashLog(L"crash.txt", err);
		return FALSE;
	}
	else if (FAILED(result))
	{
		if (errors)
		{
			CrashManager::CrashLog(L"crash.txt", errors);
		}
		return FALSE;
	}
	*/

	size_t size = filesize(filename);
	std::ifstream input(filename, std::ifstream::binary | std::istream::in);
	if (input.fail()) { return FALSE; }
	uint8_t * ptr = new uint8_t[size];
	input.read((char *)(ptr), size);
	input.close();

	result = device->CreatePixelShader(ptr, size, NULL, &ps_);
	if (FAILED(result)) { return FALSE; }
	/*
	shaderBuffer->Release();
	shaderBuffer = NULL;*/

	return TRUE;
}

BOOL Material::CreateTransformMatrixBuffer(ID3D11Device * device)
{
	D3D11_BUFFER_DESC description;
	description.Usage = D3D11_USAGE_DYNAMIC;
	description.ByteWidth = sizeof TransformMatrixBuffer;
	description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	description.MiscFlags = 0;
	description.StructureByteStride = 0;

	HRESULT result = device->CreateBuffer(&description, NULL, &transformMatrixBuffer_);
	if (FAILED(result)) { return FALSE; }

	return TRUE;
}

BOOL Material::UpdateTransformation(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix)
{
	// All this matrices must be transposed. It's just a requirement of DirectX 11.
	world_matrix = DirectX::XMMatrixTranspose(world_matrix);
	view_matrix = DirectX::XMMatrixTranspose(view_matrix);
	projection_matrix = DirectX::XMMatrixTranspose(projection_matrix);

	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = device_context->Map(transformMatrixBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	if (FAILED(result)) { return FALSE; }

	auto inside_data = (TransformMatrixBuffer *)(resource.pData);
	inside_data->world = world_matrix;
	inside_data->view = view_matrix;
	inside_data->projection = projection_matrix;

	device_context->Unmap(transformMatrixBuffer_, 0);

	return TRUE;
}

BOOL Material::CreateLightBuffer(ID3D11Device * device)
{
	D3D11_BUFFER_DESC description;
	description.Usage = D3D11_USAGE_DYNAMIC;
	description.ByteWidth = sizeof Light::LightBuffer * MAX_LIGHT_PER_LOCATION_COUNT;
	description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	description.MiscFlags = 0;
	description.StructureByteStride = 0;

	HRESULT result = device->CreateBuffer(&description, NULL, &lightBuffer_);
	if (FAILED(result)) { return FALSE; }

	return TRUE;
}

BOOL Material::UpdateLight(ID3D11DeviceContext * device_context, Pool<Light> * lights)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = device_context->Map(lightBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	if (FAILED(result)) { return FALSE; }

	Light::LightBuffer * ptr = reinterpret_cast<Light::LightBuffer *>(resource.pData);
	for (auto iLight = lights->Begin(); iLight != lights->End(); ++iLight)
	{
		*ptr = iLight->GenerateBuffer();
		++ptr;
	}
	//*ptr = light->GenerateBuffer();
	device_context->Unmap(lightBuffer_, 0);

	return TRUE;
}

BOOL Material::CreateMaterialBuffer(ID3D11Device * device)
{
	D3D11_BUFFER_DESC description;
	description.Usage = D3D11_USAGE_DYNAMIC;
	description.ByteWidth = sizeof MaterialBuffer;
	description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	description.MiscFlags = 0;
	description.StructureByteStride = 0;

	HRESULT result = device->CreateBuffer(&description, NULL, &m_materialBuffer);
	if (FAILED(result)) { return FALSE; }

	return TRUE;
}

BOOL Material::UpdateMaterialBuffer(ID3D11DeviceContext * device_context)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	HRESULT result = device_context->Map(m_materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	if (FAILED(result)) { return FALSE; }

	MaterialBuffer * ptr = reinterpret_cast<MaterialBuffer *>(resource.pData);
	ptr->mDiffuse = m_diffuse;
	ptr->mAmbient = m_ambient;
	ptr->mSpecular = m_specular;
	ptr->mRoughness = m_roughness;
	ptr->mTransparency = m_transparency;
	ptr->mMirror = m_mirror;
	ptr->mIOR = m_IOR;
	device_context->Unmap(m_materialBuffer, 0);
	return TRUE;
}

VOID Material::DrawObject(ID3D11DeviceContext * device_context, UINT index_count, ID3D11ShaderResourceView * srv)
{
	device_context->IASetInputLayout(il_);
	device_context->VSSetShader(vs_, NULL, 0);
	device_context->PSSetShader(ps_, NULL, 0);
	device_context->VSSetConstantBuffers(0, 1, &transformMatrixBuffer_);
	device_context->PSSetConstantBuffers(0, 1, &lightBuffer_);
	device_context->PSSetConstantBuffers(1, 1, &m_materialBuffer);
	device_context->PSSetSamplers(0, 1, &sampler_);
	device_context->PSSetShaderResources(0, 1, &srv);
	device_context->DrawIndexed(index_count, 0, 0);
}

VOID Material::Destroy()
{
	if (vs_)
	{
		vs_->Release();
		vs_ = NULL;
	}
	if (ps_)
	{
		ps_->Release();
		ps_ = NULL;
	}
	if (il_)
	{
		il_->Release();
		il_ = NULL;
	}
	if (transformMatrixBuffer_)
	{
		transformMatrixBuffer_->Release();
		transformMatrixBuffer_ = NULL;
	}
	if (lightBuffer_)
	{
		lightBuffer_->Release();
		lightBuffer_ = NULL;
	}
	if (sampler_)
	{
		sampler_->Release();
		sampler_ = NULL;
	}
}

DirectX::XMVECTOR Material::GetDiffuseXM()
{  
	return DirectX::XMVectorSet(m_diffuse.x, m_diffuse.y, m_diffuse.z, 1.0f);
}

VOID Material::SetDiffuseXM(DirectX::XMVECTOR diffuse)
{ 
	DirectX::XMStoreFloat4(&m_diffuse, diffuse);
}

VOID Material::GetDiffuse(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_diffuse.x;
	g = m_diffuse.y;
	b = m_diffuse.z;
}

VOID Material::SetDiffuse(FLOAT r, FLOAT g, FLOAT b)
{
	m_diffuse.x = r;
	m_diffuse.y = g;
	m_diffuse.z = b;
}

DirectX::XMVECTOR Material::GetAmbientXM()
{
	return DirectX::XMVectorSet(m_ambient.x, m_ambient.y, m_ambient.z, 1.0f);
}

VOID Material::SetAmbientXM(DirectX::XMVECTOR ambient)
{
	DirectX::XMStoreFloat4(&m_ambient, ambient);
}

VOID Material::GetAmbient(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_ambient.x;
	g = m_ambient.y;
	b = m_ambient.z;
}

VOID Material::SetAmbient(FLOAT r, FLOAT g, FLOAT b)
{
	m_ambient.x = r;
	m_ambient.y = g;
	m_ambient.z = b;
}

DirectX::XMVECTOR Material::GetSpecularXM()
{
	return DirectX::XMVectorSet(m_specular.x, m_specular.y, m_specular.z, 1.0f);
}

VOID Material::SetSpecularXM(DirectX::XMVECTOR specular)
{
	DirectX::XMStoreFloat4(&m_specular, specular);
}

VOID Material::GetSpecular(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_specular.x;
	g = m_specular.y;
	b = m_specular.z;
}

VOID Material::SetSpecular(FLOAT r, FLOAT g, FLOAT b)
{
	m_specular.x = r;
	m_specular.y = g;
	m_specular.z = b;
}

FLOAT Material::GåtRoughness()
{
	return m_roughness;
}

VOID Material::SetRoughness(FLOAT roughness)
{
	m_roughness = roughness;
}

FLOAT Material::GåtTransparency()
{
	return m_transparency;
}

VOID Material::SetTransparency(FLOAT transparency)
{
	m_transparency = transparency;
}

FLOAT Material::GåtMirror()
{
	return m_mirror;
}

VOID Material::SetMirror(FLOAT mirror)
{
	m_mirror = mirror;
}

FLOAT Material::GåtIOR()
{
	return m_IOR;
}

VOID Material::SetIOR(FLOAT ior)
{
	m_IOR = ior;
}