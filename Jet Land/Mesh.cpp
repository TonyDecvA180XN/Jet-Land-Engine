#include "Mesh.h"

Mesh::Mesh()
{
	m_vertexArray = NULL;
	m_indexArray = NULL;
	m_indexCount = 0;
	m_vertexCount = 0;
	m_vFormat = 0;
	m_vertexSize = 0;
}

Mesh::~Mesh()
= default;

VOID * Mesh::GetVertices()
{
	return m_vertexArray;
}

UINT Mesh::GetVertexCount()
{
	return m_vertexCount;
}

UINT Mesh::GetVertexSize()
{
	return m_vertexSize;
}

UINT * Mesh::GetIndices()
{
	return m_indexArray;
}

UINT Mesh::GetIndexCount()
{
	return m_indexCount;
}

VFORMAT Mesh::GetVertexFormat()
{
	return m_vFormat;
}

VOID Mesh::Terminate()
{
	if (m_vertexArray)
	{
		delete[] m_vertexArray;
		m_vertexArray = NULL;
	}
	if (m_indexArray)
	{
		delete[] m_indexArray;
		m_indexArray = NULL;
	}
	m_vertexCount = m_indexCount = m_vertexSize = 0;
	PoolObject::Terminate();
}
