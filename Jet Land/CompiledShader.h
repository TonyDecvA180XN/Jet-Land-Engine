#pragma once

#include "PoolObject.h"

class CompiledShader : public PoolObject
{
public:
	CompiledShader();
	~CompiledShader();

	uint8_t * Get();
	size_t GetSize();

	VOID Terminate() override;
private:
	friend class Loader;

	size_t m_size;
	uint8_t * m_buffer;
};

