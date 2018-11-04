#include "LightCommonComponent.h"


LightCommonComponent::LightCommonComponent() :
	m_lb(NULL),
	m_lights(LIMIT_AMOUNT_OF_LIGHTS)
{
}


LightCommonComponent::~LightCommonComponent()
{
}

VOID LightCommonComponent::Create(ID3D11Device * device)
{

	D3D11_BUFFER_DESC lbDescription;
	lbDescription.Usage = D3D11_USAGE_DYNAMIC; // may updates after creating
	lbDescription.ByteWidth = sizeof Light::LightBuffer * LIMIT_AMOUNT_OF_LIGHTS; // size of all light's buffers
	lbDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // GPU cannot write
	lbDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU can write
	lbDescription.MiscFlags = 0; // bullshit
	lbDescription.StructureByteStride = 0; // bullshit

	device->CreateBuffer(&lbDescription, NULL, &m_lb);
}

VOID LightCommonComponent::Destroy()
{
	ReleaseCOM(m_lb);
}

VOID LightCommonComponent::Update(ID3D11DeviceContext * device_context)
{
	if (m_lights.AnyUpdates())
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		HRESULT result = device_context->Map(m_lb, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

		auto inside_data = (Light::LightBuffer *)(resource.pData);
		for (UINT i = 0; i < LIMIT_AMOUNT_OF_LIGHTS; ++i)
		{
			inside_data[i] = m_lights.GetItem(i)->GenerateBuffer();
		}

		device_context->Unmap(m_lb, 0);
	}
}

ID3D11Buffer ** LightCommonComponent::GetBufferLP()
{
	return &m_lb;
}

Pool<Light> * LightCommonComponent::GetPool()
{
	return &m_lights;
}