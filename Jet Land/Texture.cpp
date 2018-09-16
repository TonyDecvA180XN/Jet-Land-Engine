#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

BOOL Texture::LoadFromFile(ID3D11Device * device, std::wstring & filename)
{
	return SUCCEEDED(DirectX::CreateDDSTextureFromFile(device, filename.c_str(), NULL, &m_srv));
}

BOOL Texture::LoadFromMem(ID3D11Device * device, uint8_t * data_ptr, size_t data_size)
{
	return SUCCEEDED(DirectX::CreateDDSTextureFromMemory(device, data_ptr, data_size, NULL, &m_srv));
}

ID3D11ShaderResourceView * Texture::Get()
{
	return m_srv;
}

VOID Texture::Unload()
{
	if (m_srv)
	{
		m_srv->Release();
		m_srv = NULL;
	}
}
