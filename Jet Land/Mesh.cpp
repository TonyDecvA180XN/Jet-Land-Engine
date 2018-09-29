#include "Mesh.h"



Mesh::Mesh()
{
    vertexArray_ = NULL;
    indexArray_ = NULL;
    indexCount_ = 0;
    vertexCount_ = 0;
    vertexBuffer_ = NULL;
    indexBuffer_ = NULL;
    vertexFormat_ = VERTEX_FORMAT_POSITION;
    vertexSize_ = 0;
}


Mesh::~Mesh()
= default;

BOOL Mesh::Create()
{
//
//    vertexCount_ = 8;
//    indexCount_ = 36;
//
//    indexArray_ = new UINT[indexCount_];
//    if (!indexArray_) { return FALSE; }
//    vertexArray_ = new VERTEX[vertexCount_];
//    if (!vertexArray_) { return FALSE; }
//
//
//    vertexArray_[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f);
//    vertexArray_[0].normal = DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f);
//
//    vertexArray_[1].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f);
//    vertexArray_[1].normal = DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f);
//
//    vertexArray_[2].position = DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f);
//    vertexArray_[2].normal = DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f);
//
//    vertexArray_[3].position = DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f);
//    vertexArray_[3].normal = DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f);
//
//    vertexArray_[4].position = DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f);
//    vertexArray_[4].normal = DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f);
//
//    vertexArray_[5].position = DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f);
//    vertexArray_[5].normal = DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f);
//
//    vertexArray_[6].position = DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f);
//    vertexArray_[6].normal = DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f);
//
//    vertexArray_[7].position = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
//    vertexArray_[7].normal = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
//
//
//#ifdef  VS_COLOR
//    vertexArray_[0].color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
//    vertexArray_[1].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//    vertexArray_[2].color = DirectX::XMFLOAT4(1.0f, 0.0, 0.0f, 1.0f);
//    vertexArray_[3].color = DirectX::XMFLOAT4(0.0f, 1.0, 0.0f, 1.0f);
//    vertexArray_[4].color = DirectX::XMFLOAT4(0.0f, 0.0, 1.0f, 1.0f);
//    vertexArray_[5].color = DirectX::XMFLOAT4(1.0f, 0.0, 1.0f, 1.0f);
//    vertexArray_[6].color = DirectX::XMFLOAT4(0.0f, 1.0, 1.0f, 1.0f);
//    vertexArray_[7].color = DirectX::XMFLOAT4(1.0f, 1.0, 0.0f, 1.0f);
//#endif //  VS_COLOR
//
//    indexArray_[0] = 7;
//    indexArray_[1] = 3;
//    indexArray_[2] = 1;
//
//    indexArray_[3] = 7;
//    indexArray_[4] = 1;
//    indexArray_[5] = 5;
//
//    indexArray_[6] = 2;
//    indexArray_[7] = 6;
//    indexArray_[8] = 0;
//
//    indexArray_[9] = 0;
//    indexArray_[10] = 6;
//    indexArray_[11] = 4;
//
//    indexArray_[12] = 2;
//    indexArray_[13] = 3;
//    indexArray_[14] = 7;
//
//    indexArray_[15] = 2;
//    indexArray_[16] = 7;
//    indexArray_[17] = 6;
//
//    indexArray_[18] = 4;
//    indexArray_[19] = 6;
//    indexArray_[20] = 7;
//
//    indexArray_[21] = 4;
//    indexArray_[22] = 7;
//    indexArray_[23] = 5;
//
//    indexArray_[24] = 1;
//    indexArray_[25] = 3;
//    indexArray_[26] = 2;
//
//    indexArray_[27] = 1;
//    indexArray_[28] = 2;
//    indexArray_[29] = 0;
//
//    indexArray_[30] = 5;
//    indexArray_[31] = 1;
//    indexArray_[32] = 0;
//
//    indexArray_[33] = 5;
//    indexArray_[34] = 0;
//    indexArray_[35] = 4;
//
    return TRUE;
}


VOID Mesh::Load(std::string * filename)
{
    LoadMeshObjFromFile(filename, &vertexFormat_, &vertexArray_, &vertexCount_, &vertexSize_, &indexArray_, &indexCount_);
    /*for (int i = 0; i != vertexCount_; i++)
    {
        //DirectX::XMFLOAT3 pos = ((Vertex_PN *)vertexArray_)[i * vertexSize_].position;
        DirectX::XMFLOAT3 nrm = ((Vertex_PN *)vertexArray_)[i * vertexSize_].normal;
        continue;
    }*/
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
    vertexCount_ = indexCount_ = vertexSize_ = 0;
}

BOOL Mesh::FillVertexBuffer(ID3D11Device * device)
{
    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexDataDesc;

    vertexBufferDesc.ByteWidth = vertexCount_ * vertexSize_;
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
    UINT stride = vertexSize_;
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

VERTEX_FORMAT Mesh::GetVertexFormat()
{
    return vertexFormat_;
}

