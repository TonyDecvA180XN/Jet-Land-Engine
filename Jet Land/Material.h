#pragma once

#include "Globals.h"
#include "LightSource.h"
#include "Pool.h"


#include "VertexMode.h"
#include "CrashManager.h"

class Material
{
public:
    Material();
    ~Material();

    BOOL LoadVertexShaderAndInputLayout(ID3D11Device * device, LPSTR filename, VERTEX_FORMAT vertex_format);
    BOOL LoadPixelShader(ID3D11Device * device, LPSTR filename);

    BOOL CreateTransformMatrixBuffer(ID3D11Device * device);
    BOOL UpdateTransformation(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix);

    BOOL CreateLightBuffer(ID3D11Device * device);
    BOOL UpdateLight(ID3D11DeviceContext * device_context, Pool<Light> * lights);

    VOID DrawObject(ID3D11DeviceContext * device_context, UINT index_count, ID3D11ShaderResourceView * srv);

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
    ID3D11Buffer * lightBuffer_;
	ID3D11SamplerState * sampler_;
};

