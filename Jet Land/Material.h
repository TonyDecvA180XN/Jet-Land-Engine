#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "VertexModeSelector.h"
#include "CrashManager.h"

class Material
{
public:
    Material();
    ~Material();

    BOOL LoadVertexShaderAndInputLayout(ID3D11Device * device, LPTSTR filename);
    BOOL LoadPixelShader(ID3D11Device * device, LPTSTR filename);

    BOOL CreateTransformMatrixBuffer(ID3D11Device * device);
    BOOL UpdateTransformation(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix);

    VOID DrawObject(ID3D11DeviceContext * device_context, UINT index_count);

    VOID Destroy();

private:
    struct TransformMatrixBuffer
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };


private:
    ID3D11VertexShader * vs_;
    ID3D11PixelShader * ps_;
    ID3D11InputLayout * il_;
    ID3D11Buffer * transformMatrixBuffer_;

};

