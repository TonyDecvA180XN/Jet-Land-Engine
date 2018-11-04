#include "Texture.h"

Texture::Texture()
= default;

Texture::~Texture()
= default;

ID3D11ShaderResourceView * Texture::Get()
{
	return m_srv;
}

VOID Texture::Terminate()
{
	if (m_srv)
	{
		m_srv->Release();
		m_srv = NULL;
	}
	PoolObject::Terminate();
}
