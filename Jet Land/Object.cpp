#include "Object.h"



Object::Object(): Object(LPTSTR(L""))
{
}


Object::Object(LPTSTR name) : name_(name)
{
    mesh_ = NULL;
    material_ = NULL;
}

Object::~Object()
= default;

BOOL Object::CreateMesh(ID3D11Device * device)
{
    BOOL result;

    mesh_ = new Mesh;
    if (!mesh_) { return FALSE; }

    result = mesh_->Create();
    if (!result) { return FALSE; }

    result = mesh_->FillVertexBuffer(device);
    if (!result) { return FALSE; }

    result = mesh_->FillIndexBuffer(device);
    if (!result) { return FALSE; }

    return TRUE;
}

VOID Object::DestroyMesh()
{
    if (mesh_)
    {
        mesh_->Destroy();
        delete mesh_;
        mesh_ = NULL;
    }
}

BOOL Object::CreateMaterial(ID3D11Device * device, LPTSTR vs_filename, LPTSTR ps_filename)
{
    BOOL result;

    material_ = new Material;
    if (!material_) { return FALSE; }

    result = material_->LoadVertexShaderAndInputLayout(device, vs_filename);
    if (!result) { return FALSE; }

    result = material_->LoadPixelShader(device, ps_filename);
    if (!result) { return FALSE; }

    result = material_->CreateTransformMatrixBuffer(device);
    if (!result) { return FALSE; }

    return TRUE;
}

VOID Object::DestroyMaterial()
{
    if (material_)
    {
        material_->Destroy();
        delete material_;
        material_ = NULL;
    }
}

VOID Object::Render(ID3D11DeviceContext * device_context, DirectX::XMMATRIX world_matrix, DirectX::XMMATRIX view_matrix, DirectX::XMMATRIX projection_matrix)
{
    mesh_->ApplyBuffers(device_context);
    material_->UpdateTransformation(device_context, world_matrix, view_matrix, projection_matrix);
    material_->DrawObject(device_context, mesh_->GetIndexCount());
}
