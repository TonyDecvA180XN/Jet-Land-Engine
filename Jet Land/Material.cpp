#include "Material.h"



Material::Material()
{
    vs_ = NULL;
    ps_ = NULL;
    il_ = NULL;

    transformMatrixBuffer_ = NULL;
    lightBuffer_ = NULL;
}


Material::~Material()
= default;

BOOL Material::LoadVertexShaderAndInputLayout(ID3D11Device * device, LPTSTR filename, VERTEX_FORMAT vertex_format)
{
    HRESULT result;

    ID3D10Blob * shaderBuffer;
    ID3D10Blob * errors;
    result = D3DCompileFromFile(filename, NULL, NULL, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBuffer, &errors);
    if (result == ERROR_FILE_NOT_FOUND)
    {
        std::wstring err;
        err += L"Error opening shader source file\n";
        err += L"Cannot find file \"";
        err += filename;
        err += L"\".\n\n";
        CrashManager::CrashLog(L"crash.txt", err);
        return FALSE;
    }
    else if (FAILED(result))
    {
        if (errors)
        {
            CrashManager::CrashLog(L"crash.txt", errors);
        }
        return FALSE;
    }

    result = device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &vs_);
    if (FAILED(result)) { return FALSE; }

    UINT ilElementsCount = 0;
    D3D11_INPUT_ELEMENT_DESC * descriptions = new D3D11_INPUT_ELEMENT_DESC[5];
    if (!descriptions) { return FALSE; }

    if (vertex_format & VertexComponent::HavePosition)
    {
        descriptions[ilElementsCount].SemanticName = "POSITION";
        descriptions[ilElementsCount].SemanticIndex = 0;
        descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        descriptions[ilElementsCount].InputSlot = 0;
        descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        descriptions[ilElementsCount].InstanceDataStepRate = 0;
        ilElementsCount++;
    }

    if (vertex_format & VertexComponent::HaveColor)
    {
    descriptions[ilElementsCount].SemanticName = "VERTEXCOLOR";
    descriptions[ilElementsCount].SemanticIndex = 0;
    descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    descriptions[ilElementsCount].InputSlot = 0;
    descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    descriptions[ilElementsCount].InstanceDataStepRate = 0;
    ilElementsCount++;
    }

    if (vertex_format & VertexComponent::HaveNormal)
    {
    descriptions[ilElementsCount].SemanticName = "NORMAL";
    descriptions[ilElementsCount].SemanticIndex = 0;
    descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    descriptions[ilElementsCount].InputSlot = 0;
    descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    descriptions[ilElementsCount].InstanceDataStepRate = 0;
    ilElementsCount++;
    }

    if (vertex_format & VertexComponent::HaveTexcoords)
    {
        descriptions[ilElementsCount].SemanticName = "TEXCOORDS";
        descriptions[ilElementsCount].SemanticIndex = 0;
        descriptions[ilElementsCount].Format = DXGI_FORMAT_R32G32_FLOAT;
        descriptions[ilElementsCount].InputSlot = 0;
        descriptions[ilElementsCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        descriptions[ilElementsCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        descriptions[ilElementsCount].InstanceDataStepRate = 0;
        ilElementsCount++;
    }

    result = device->CreateInputLayout(descriptions, ilElementsCount, shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), &il_);
    if (FAILED(result)) { return FALSE; }

    shaderBuffer->Release();
    shaderBuffer = NULL;

    //delete[] descriptions;

    return TRUE;
}

BOOL Material::LoadPixelShader(ID3D11Device * device, LPTSTR filename)
{
    HRESULT result;

    ID3D10Blob * shaderBuffer;
    ID3D10Blob * errors;
    result = D3DCompileFromFile(filename, NULL, NULL, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBuffer, &errors);
    if (result == ERROR_FILE_NOT_FOUND)
    {
        std::wstring err;
        err += L"Error opening shader source file\n";
        err += L"Cannot find file \"";
        err += filename;
        err += L"\".\n\n";
        CrashManager::CrashLog(L"crash.txt", err);
        return FALSE;
    }
    else if (FAILED(result))
    {
        if (errors)
        {
            CrashManager::CrashLog(L"crash.txt", errors);
        }
        return FALSE;
    }

    result = device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &ps_);
    if (FAILED(result)) { return FALSE; }
    shaderBuffer->Release();
    shaderBuffer = NULL;

    return TRUE;
}

BOOL Material::CreateTransformMatrixBuffer(ID3D11Device * device)
{
    D3D11_BUFFER_DESC description;
    description.Usage = D3D11_USAGE_DYNAMIC;
    description.ByteWidth = sizeof TransformMatrixBuffer;
    description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    description.MiscFlags = 0;
    description.StructureByteStride = 0;

    HRESULT result = device->CreateBuffer(&description, NULL, &transformMatrixBuffer_);
    if (FAILED(result)) { return FALSE; }

    return TRUE;
}

BOOL Material::UpdateTransformation(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix)
{
    // All this matrices must be transposed. It's just a requirement of DirectX 11.
    world_matrix = DirectX::XMMatrixTranspose(world_matrix);
    view_matrix = DirectX::XMMatrixTranspose(view_matrix);
    projection_matrix = DirectX::XMMatrixTranspose(projection_matrix);

    D3D11_MAPPED_SUBRESOURCE resource;
    HRESULT result = device_context->Map(transformMatrixBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    if (FAILED(result)) { return FALSE; }

    auto inside_data = (TransformMatrixBuffer *)(resource.pData);
    inside_data->world = world_matrix;
    inside_data->view = view_matrix;
    inside_data->projection = projection_matrix;

    device_context->Unmap(transformMatrixBuffer_, 0);

    return TRUE;
}

BOOL Material::CreateLightBuffer(ID3D11Device * device)
{
    D3D11_BUFFER_DESC description;
    description.Usage = D3D11_USAGE_DYNAMIC;
    description.ByteWidth = sizeof LightBuffer;
    description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    description.MiscFlags = 0;
    description.StructureByteStride = 0;

    HRESULT result = device->CreateBuffer(&description, NULL, &lightBuffer_);
    if (FAILED(result)) { return FALSE; }

    return TRUE;
}

BOOL Material::UpdateLight(ID3D11DeviceContext * device_context, LightSourceDirect * light)
{
    D3D11_MAPPED_SUBRESOURCE resource;
    HRESULT result = device_context->Map(lightBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    if (FAILED(result)) { return FALSE; }

    auto inside_data = (LightBuffer *)(resource.pData);
    inside_data->sunColor = light->GetColor();
    inside_data->direction = light->GetDirection();

    device_context->Unmap(lightBuffer_, 0);

    return TRUE;
}

VOID Material::DrawObject(ID3D11DeviceContext * device_context, UINT index_count)
{
    device_context->IASetInputLayout(il_);
    device_context->VSSetShader(vs_, NULL, 0);
    device_context->PSSetShader(ps_, NULL, 0);
    device_context->VSSetConstantBuffers(0, 1, &transformMatrixBuffer_);
    device_context->PSSetConstantBuffers(0, 1, &lightBuffer_);
    device_context->DrawIndexed(index_count, 0, 0);
}

VOID Material::Destroy()
{
    if (vs_)
    {
        vs_->Release();
        vs_ = NULL;
    }
    if (ps_)
    {
        ps_->Release();
        ps_ = NULL;
    }
    if (il_)
    {
        il_->Release();
        il_ = NULL;
    }
    if (transformMatrixBuffer_)
    {
        transformMatrixBuffer_->Release();
        transformMatrixBuffer_ = NULL;
    }
    if (lightBuffer_)
    {
        lightBuffer_->Release();
        lightBuffer_ = NULL;
    }
}
