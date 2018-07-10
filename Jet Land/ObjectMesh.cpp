#include "ObjectMesh.h"



ObjectMesh::ObjectMesh()
{
    mesh_ = NULL;
    material_ = NULL;
}


ObjectMesh::~ObjectMesh()
{
}

BOOL ObjectMesh::CreateMesh(ID3D11Device * device)
{
    mesh_ = new Mesh;
    if (!mesh_) { return FALSE; }

    BOOL result = mesh_->Create();
    if (!result) { return FALSE; }

    result = mesh_->FillVertexBuffer(device);
    if (!result) { return FALSE; }
    result = mesh_->FillIndexBuffer(device);
    if (!result) { return FALSE; }

    return TRUE;
}

BOOL ObjectMesh::CreateMaterial(ID3D11Device * device, LPTSTR shader_filename)
{
    material_ = new Material;
    if (!material_) { return FALSE; }

    BOOL result = material_->LoadVertexShaderAndInputLayout(device, shader_filename);
    if (!result) { return FALSE; }
    result = material_->LoadPixelShader(device, shader_filename);
    if (!result) { return FALSE; }
    result = material_->CreateTransformMatrixBuffer(device);
    if (!result) { return FALSE; }

    return TRUE;
}

BOOL ObjectMesh::Render(ID3D11DeviceContext * device_context, Camera * target_camera)
{
    mesh_->ApplyBuffers(device_context);
    BOOL result = material_->UpdateTransformation(device_context, this->GetWorldMatrix(), target_camera->GetViewMatrix(), target_camera->GetProjMatrix());
    if (!result) { return FALSE; }
    material_->DrawObject(device_context, mesh_->GetIndexCount());

    return TRUE;
}

VOID ObjectMesh::Destroy()
{
    if (mesh_)
    {
        mesh_->Destroy();
        delete mesh_;
        mesh_ = NULL;
    }
    if (material_)
    {
        material_->Destroy();
        delete material_;
        material_ = NULL;
    }
}