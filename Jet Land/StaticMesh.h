#pragma once

#include "Object3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "PoolObject.h"
#include "Pool.h"

class StaticMesh : public Object3D, public PoolObject
{
public:
    StaticMesh();
    ~StaticMesh();

    BOOL CreateMesh(ID3D11Device * device,
		std::string * mesh_filename,
		std::string * shader_v_filename,
		std::string * shader_p_filename);

    BOOL Render(ID3D11DeviceContext * device_context, Camera * target_camera, Pool<Light> * lights, ID3D11ShaderResourceView * srv);

    VOID Destroy();
private:
    Mesh * mesh_;
    Material * material_;
};

