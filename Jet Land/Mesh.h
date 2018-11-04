#pragma once

#include "PoolObject.h"
#include "OBJ_Loader.h"
#include "JMH_Loader.h"
#include "VFormat.h"

class Mesh : public PoolObject
{
public:
    Mesh();
    ~Mesh();

	VOID * GetVertices();
    UINT GetVertexCount();
	UINT GetVertexSize();

	UINT * GetIndices();
    UINT GetIndexCount();
    VFORMAT GetVertexFormat();

	VOID Terminate() override;
private:
	friend class Loader;

    VFORMAT m_vFormat;
    VOID * m_vertexArray;
    UINT * m_indexArray;
    UINT m_vertexCount, m_indexCount, m_vertexSize;
};

