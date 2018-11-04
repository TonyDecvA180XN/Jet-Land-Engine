#pragma once

#include "PoolObject.h"

class Texture : public PoolObject
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView * Get();

	VOID Terminate() override;
private:
	friend class Loader;

	ID3D11ShaderResourceView * m_srv;
};

