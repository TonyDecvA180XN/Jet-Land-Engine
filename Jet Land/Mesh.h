#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "IncluderSTD.h"
#include "VertexMode.h"
#include "OBJ_Loader.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    BOOL Create();
    VOID Load(std::wstring * filename);

    VOID Destroy();

    BOOL FillVertexBuffer(ID3D11Device * device);
    BOOL FillIndexBuffer(ID3D11Device * device);

    VOID ApplyBuffers(ID3D11DeviceContext * device_context);

    UINT GetVertexCount();
    UINT GetIndexCount();
    VERTEX_FORMAT GetVertexFormat();

private:


private:
    VERTEX_FORMAT vertexFormat_;
    VOID * vertexArray_;
    UINT * indexArray_;
    UINT vertexCount_, indexCount_, vertexSize_;

    ID3D11Buffer * vertexBuffer_;
    ID3D11Buffer * indexBuffer_;
};

