#include "StaticMesh.h"



StaticMesh::StaticMesh()
{
    mesh_ = NULL;
    material_ = NULL;
}


StaticMesh::~StaticMesh()
{
}

BOOL StaticMesh::CreateMesh(ID3D11Device * device, std::wstring * mesh_filename, LPTSTR shader_filename)
{
    mesh_ = new Mesh;
    if (!mesh_) { return FALSE; }

    BOOL result;
    mesh_->Load(mesh_filename);

    result = mesh_->FillVertexBuffer(device);
    if (!result) { return FALSE; }
    result = mesh_->FillIndexBuffer(device);
    if (!result) { return FALSE; }

    material_ = new Material;
    if (!material_) { return FALSE; }

    result = material_->LoadVertexShaderAndInputLayout(device, shader_filename, mesh_->GetVertexFormat());
    if (!result) { return FALSE; }
    result = material_->LoadPixelShader(device, shader_filename);
    if (!result) { return FALSE; }
    result = material_->CreateTransformMatrixBuffer(device);
    if (!result) { return FALSE; }
    result = material_->CreateLightBuffer(device);
    if (!result) { return FALSE; }


    return TRUE;
}

BOOL StaticMesh::Render(ID3D11DeviceContext * device_context, Camera * target_camera, LightSourceDirect * light, ID3D11ShaderResourceView * srv)
{
    mesh_->ApplyBuffers(device_context);
    BOOL result = material_->UpdateTransformation(device_context, this->GetWorldMatrix(), target_camera->GetViewMatrix(), target_camera->GetProjMatrix());
    if (!result) { return FALSE; }
    result = material_->UpdateLight(device_context, light);
    if (!result) { return FALSE; }
    material_->DrawObject(device_context, mesh_->GetIndexCount(), srv);

    return TRUE;
}

VOID StaticMesh::Destroy()
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
