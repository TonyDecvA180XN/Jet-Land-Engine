#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Object3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

class StaticMesh : public Object3D
{
public:
    StaticMesh();
    ~StaticMesh();

    BOOL CreateMesh(ID3D11Device * device);
    BOOL CreateMaterial(ID3D11Device * device, LPTSTR shader_filename);

    BOOL Render(ID3D11DeviceContext * device_context, Camera * target_camera, LightSourceDirect * light);

    VOID Destroy();
private:
    Mesh * mesh_;
    Material * material_;
};

