#include "Mesh.h"



Mesh::Mesh()
{
    vertexArray_ = NULL;
    indexArray_ = NULL;
    indexCount_ = 0;
    vertexCount_ = 0;
    vertexBuffer_ = NULL;
    indexBuffer_ = NULL;
}


Mesh::~Mesh()
= default;

BOOL Mesh::Create()
{
    vertexCount_ = 3;
    indexCount_ = 3;

    indexArray_ = new UINT[indexCount_];
    if (!indexArray_) { return FALSE; }
    vertexArray_ = new VERTEX[vertexCount_];
    if (!vertexArray_) { return FALSE; }
    

    vertexArray_[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);
    vertexArray_[0].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

    vertexArray_[1].position = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertexArray_[1].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

    vertexArray_[2].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);
    vertexArray_[2].color = DirectX::XMFLOAT4(0.0f, 0.0, 1.0f, 1.0f);

    indexArray_[0] = 2;
    indexArray_[1] = 1;
    indexArray_[2] = 0;

    return TRUE;
}

VOID Mesh::Load()
{

}

VOID Mesh::Destroy()
{
    if (vertexBuffer_)
    {
        vertexBuffer_->Release();
        vertexBuffer_ = NULL;
    }
    if (indexBuffer_)
    {
        indexBuffer_->Release();
        indexBuffer_ = NULL;
    }
    if (vertexArray_)
    {
        delete[] vertexArray_;
        vertexArray_ = NULL;
    }
    if (indexArray_)
    {
        delete[] indexArray_;
        indexArray_ = NULL;
    }
    vertexCount_ = indexCount_ = 0;
}

BOOL Mesh::FillVertexBuffer(ID3D11Device * device)
{
    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexDataDesc;

    vertexBufferDesc.ByteWidth = vertexCount_ * sizeof VERTEX;
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;
    vertexDataDesc.pSysMem = vertexArray_;
    vertexDataDesc.SysMemPitch = 0;
    vertexDataDesc.SysMemSlicePitch = 0;

    HRESULT result;
    result = device->CreateBuffer(&vertexBufferDesc, &vertexDataDesc, &vertexBuffer_);
    if (FAILED(result)) { return FALSE; }

    return TRUE;
}

BOOL Mesh::FillIndexBuffer(ID3D11Device * device)
{
    D3D11_BUFFER_DESC indexBufferDesc;
    D3D11_SUBRESOURCE_DATA indexDataDesc;

    indexBufferDesc.ByteWidth = indexCount_ * sizeof UINT;
    indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;
    indexDataDesc.pSysMem = indexArray_;
    indexDataDesc.SysMemPitch = 0;
    indexDataDesc.SysMemSlicePitch = 0;

    HRESULT result;
    result = device->CreateBuffer(&indexBufferDesc, &indexDataDesc, &indexBuffer_);
    if (FAILED(result)) { return FALSE; }

    return TRUE;
}

VOID Mesh::ApplyBuffers(ID3D11DeviceContext * device_context)
{
    UINT stride = sizeof VERTEX;
    UINT offset = 0;
    device_context->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
    device_context->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

UINT Mesh::GetVertexCount()
{
    return vertexCount_;
}

UINT Mesh::GetIndexCount()
{
    return indexCount_;
}

