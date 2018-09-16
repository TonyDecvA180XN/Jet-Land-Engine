#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "IncluderSTD.h"
#include <DDSTextureLoader.h>

class Texture
{
public:
	Texture();
	~Texture();

	BOOL LoadFromFile(ID3D11Device * device, std::wstring & filename);
	BOOL LoadFromMem(ID3D11Device * device, uint8_t * data_ptr, size_t data_size);

	ID3D11ShaderResourceView * Get();

	VOID Unload();
private:
	ID3D11ShaderResourceView * m_srv;
};

