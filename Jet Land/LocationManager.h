#pragma once



#include "Pool.h"
#include "TinyXML/tinyxml2.h"
#include "StaticMesh.h"
#include "LightSource.h"
#include "Material.h"

class LocationManager
{
public:
	LocationManager();
	~LocationManager();

	VOID Connect(Pool<Light> * lights);
	VOID Connect(Pool<StaticMesh> * meshes);
	VOID Connect(Pool<Material> * materials);
	VOID Disconnect();

	BOOL LoadFromFile(ID3D11Device * device, LPSTR filename);
	VOID UnloadAll();

private:
	BOOL LoadMesh(ID3D11Device * device, tinyxml2::XMLElement * mesh);
	BOOL LoadLight(tinyxml2::XMLElement * light);
	std::string * LoadMaterial(LPSTR name, LPSTR filename, Material * material);

private:
	tinyxml2::XMLDocument * m_locationDesc;
	Pool<StaticMesh> * m_meshes;
	Pool<Light> * m_lights;
	Pool<Material> * m_materials;
};

