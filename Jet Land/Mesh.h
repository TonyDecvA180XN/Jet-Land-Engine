#pragma once



#include "VFormat.h"
#include "OBJ_Loader.h"
#include "JMH_Loader.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    BOOL Create();
    VOID Load(std::string * filename);

    VOID Destroy();

    BOOL FillVertexBuffer(ID3D11Device * device);
    BOOL FillIndexBuffer(ID3D11Device * device);

    VOID ApplyBuffers(ID3D11DeviceContext * device_context);

    UINT GetVertexCount();
    UINT GetIndexCount();
    VFORMAT GetVertexFormat();

private:


private:
    VFORMAT vertexFormat_;
    VOID * vertexArray_;
    UINT * indexArray_;
    UINT vertexCount_, indexCount_, vertexSize_;

    ID3D11Buffer * vertexBuffer_;
    ID3D11Buffer * indexBuffer_;
};

