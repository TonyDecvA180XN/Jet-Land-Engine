#pragma once

#include "StaticMesh.h"
#include "Pool.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "LightCommonComponent.h"
#include "CompiledShader.h"
#include "Camera.h"

class Loader
{
public:
	static Mesh * LoadMesh(Pool<Mesh> * pool, std::string name, std::string filename);
	static Texture * LoadTexture(Pool<Texture> * pool, std::string name, std::string filename, ID3D11Device * device);
	static Material * LoadMaterial(Pool<Material> * pool, std::string name, std::string filename);
	static Light * LoadLight(LightCommonComponent * lights, std::string name, std::string filename);
	static CompiledShader * LoadShader(Pool<CompiledShader> * pool, std::string name, std::string filename);
	static VOID LoadLocation(ID3D11Device * device, std::string filename, Pool<StaticMesh> * static_meshes,
		Pool<Mesh> * meshes, Pool<Texture> * textures, LightCommonComponent * lights, Pool<Material> * materials, Camera * camera, Pool<CompiledShader> * shaders);
};

