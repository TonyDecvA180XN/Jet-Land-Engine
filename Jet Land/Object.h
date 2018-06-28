#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Mesh.h"
#include "Material.h"

class Object
{
public:
    Object();
    Object(LPTSTR name);
    ~Object();

    BOOL CreateMesh(ID3D11Device * device);
    VOID DestroyMesh();

    BOOL CreateMaterial(ID3D11Device * device, LPTSTR vs_filename, LPTSTR ps_filename);
    VOID DestroyMaterial();

    VOID Render(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix);

private:
    LPTSTR name_;
    Mesh * mesh_;
    Material * material_;
};

