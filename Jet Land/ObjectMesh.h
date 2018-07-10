#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "Object3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

class ObjectMesh : Object3D
{
public:
    ObjectMesh();
    ~ObjectMesh();

    BOOL CreateMesh(ID3D11Device * device);
    BOOL CreateMaterial(ID3D11Device * device, LPTSTR shader_filename);

    BOOL Render(ID3D11DeviceContext * device_context, Camera * target_camera);

    VOID Destroy();
private:
    Mesh * mesh_;
    Material * material_;
};

