#pragma once




#include "Object3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

class StaticMesh : public Object3D
{
public:
    StaticMesh();
    ~StaticMesh();

    BOOL CreateMesh(ID3D11Device * device, std::wstring * mesh_filename, LPTSTR shader_v_filename, LPTSTR shader_p_filename);

    BOOL Render(ID3D11DeviceContext * device_context, Camera * target_camera, Light * light, ID3D11ShaderResourceView * srv);

    VOID Destroy();
private:
    Mesh * mesh_;
    Material * material_;
};

