#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "VertexModeSelector.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    BOOL Create();
    VOID Load();

    VOID Destroy();

    BOOL FillVertexBuffer(ID3D11Device * device);
    BOOL FillIndexBuffer(ID3D11Device * device);

    VOID ApplyBuffers(ID3D11DeviceContext * device_context);

    UINT GetVertexCount();
    UINT GetIndexCount();
private:
    struct VERTEX
    {
#ifdef VS_POSITION
        DirectX::XMFLOAT3 position{};
#endif // VS_POSITION

#ifdef VS_COLOR
        DirectX::XMFLOAT4 color{};
#endif // VS_COLOR
    };

private:
    VERTEX * vertexArray_;
    UINT * indexArray_;
    UINT vertexCount_, indexCount_;

    ID3D11Buffer * vertexBuffer_;
    ID3D11Buffer * indexBuffer_;
};

