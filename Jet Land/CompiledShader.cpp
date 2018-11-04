#include "CompiledShader.h"

CompiledShader::CompiledShader()
= default;

CompiledShader::~CompiledShader()
= default;

uint8_t * CompiledShader::Get()
{
	return m_buffer;
}

size_t CompiledShader::GetSize()
{
	return m_size;
}

VOID CompiledShader::Terminate()
{
	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
		m_size = 0;
	}
	PoolObject::Terminate();
}
