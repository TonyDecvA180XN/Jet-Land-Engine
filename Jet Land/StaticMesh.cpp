#include "StaticMesh.h"



StaticMesh::StaticMesh()
{
    mesh_ = NULL;
    material_ = NULL;
}


StaticMesh::~StaticMesh()
{
}

BOOL StaticMesh::CreateMesh(ID3D11Device * device,
	std::string * mesh_filename,
	Material * material,
	std::string * shader_filename)
{
    mesh_ = new Mesh;
    if (!mesh_) { return FALSE; }

    BOOL result;
    mesh_->Load(mesh_filename);

    result = mesh_->FillVertexBuffer(device);
    if (!result) { return FALSE; }
    result = mesh_->FillIndexBuffer(device);
    if (!result) { return FALSE; }

	material_ = material;
    if (!material_) { return FALSE; }

    result = material_->LoadVertexShaderAndInputLayout(device, (LPSTR)(*shader_filename + "_v.cso").c_str(), mesh_->GetVertexFormat());
    if (!result) { return FALSE; }
    result = material_->LoadPixelShader(device, (LPSTR)(*shader_filename + "_p.cso").c_str());
    if (!result) { return FALSE; }
    result = material_->CreateTransformMatrixBuffer(device);
    if (!result) { return FALSE; }
    result = material_->CreateLightBuffer(device);
    if (!result) { return FALSE; }
	result = material_->CreateMaterialBuffer(device);
	if (!result) { return FALSE; }

    return TRUE;
}

BOOL StaticMesh::Render(ID3D11DeviceContext * device_context, Camera * target_camera, Pool<Light> * lights, ID3D11ShaderResourceView * srv)
{
    mesh_->ApplyBuffers(device_context);
    BOOL result = material_->UpdateTransformation(device_context, this->GetWorldMatrix(), target_camera->GetViewMatrix(), target_camera->GetProjMatrix());
    if (!result) { return FALSE; }
    result = material_->UpdateLight(device_context, lights);
    if (!result) { return FALSE; }
	result = material_->UpdateMaterialBuffer(device_context);
	if (!result) { return FALSE; }
    material_->DrawObject(device_context, mesh_->GetIndexCount(), srv);

    return TRUE;
}

VOID StaticMesh::Destroy()
{
	this->Terminate();
    if (mesh_)
    {
        mesh_->Destroy();
        delete mesh_;
        mesh_ = NULL;
    }
    if (material_)
    {
		// \todo destroy
    }
}
