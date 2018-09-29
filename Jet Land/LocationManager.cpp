#include "LocationManager.h"

LocationManager::LocationManager()
{
	m_meshes = NULL;
	m_lights = NULL;
	m_locationDesc = NULL;
}


LocationManager::~LocationManager()
{
}

VOID LocationManager::Connect(Pool<Light>* lights)
{
	m_lights = lights;
}

VOID LocationManager::Connect(Pool<StaticMesh> * meshes)
{
	m_meshes = meshes;
}

VOID LocationManager::Disconnect()
{
	m_lights = NULL;
	m_meshes = NULL;
}

BOOL LocationManager::LoadFromFile(ID3D11Device * device, LPSTR filename)
{
	m_locationDesc = new tinyxml2::XMLDocument;
	if (!m_locationDesc) { return FALSE; }
	m_locationDesc->LoadFile(filename);

	tinyxml2::XMLElement * location = m_locationDesc->FirstChildElement("Location");

	tinyxml2::XMLElement * worldSettings = location->FirstChildElement("World");
	// \todo take world settings
	tinyxml2::XMLElement * layout = location->FirstChildElement("Layout");
	tinyxml2::XMLElement * meshes = layout->FirstChildElement("Meshes");

	tinyxml2::XMLElement * iStaticMesh = meshes->FirstChildElement();
	while (iStaticMesh != NULL)
	{
		this->LoadMesh(device, iStaticMesh);
		iStaticMesh = iStaticMesh->NextSiblingElement();
	}

	tinyxml2::XMLElement * lights = layout->FirstChildElement("Lights");

	tinyxml2::XMLElement * iLight = lights->FirstChildElement();
	while (iLight != NULL)
	{
		this->LoadLight(iLight);
		iLight = iLight->NextSiblingElement();
	}


	return TRUE;
}

VOID LocationManager::UnloadAll()
{
	if (m_meshes)
	{
		m_meshes->Clear();
	}
	if (m_lights)
	{
		m_lights->Clear();
	}
}

BOOL LocationManager::LoadMesh(ID3D11Device * device, tinyxml2::XMLElement * mesh)
{
	tinyxml2::XMLElement * modelName = mesh->FirstChildElement("Model");
	tinyxml2::XMLElement * position = mesh->FirstChildElement("Position");
	tinyxml2::XMLElement * rotation = mesh->FirstChildElement("Rotation");
	tinyxml2::XMLElement * scale = mesh->FirstChildElement("Scale");
	tinyxml2::XMLElement * shaderName = mesh->FirstChildElement("Shader");

	StaticMesh * newMesh;
	m_meshes->Allocate(&newMesh);
	std::string mf(modelName->Attribute("filename"));
	std::string vsf(shaderName->Attribute("filename"));
	std::string psf(shaderName->Attribute("filename"));
	vsf += "_v.cso";
	psf += "_p.cso";
	newMesh->CreateMesh(device, &mf, &vsf, &psf);

	newMesh->SetPosition(position->FloatAttribute("x"), position->FloatAttribute("y"), position->FloatAttribute("z"));
	newMesh->SetRotation(rotation->FloatAttribute("x"), rotation->FloatAttribute("y"), rotation->FloatAttribute("z"));
	newMesh->SetScaling(scale->FloatAttribute("x"), scale->FloatAttribute("y"), scale->FloatAttribute("z"));
	return TRUE;
}

BOOL LocationManager::LoadLight(tinyxml2::XMLElement * light)
{
	tinyxml2::XMLElement * color = light->FirstChildElement("Color");
	tinyxml2::XMLElement * position = light->FirstChildElement("Position");
	tinyxml2::XMLElement * direction = light->FirstChildElement("Direction");
	tinyxml2::XMLElement * radius = light->FirstChildElement("Radius");
	tinyxml2::XMLElement * angle = light->FirstChildElement("Angle");
	tinyxml2::XMLElement * type = light->FirstChildElement("Type");
	tinyxml2::XMLElement * falloff = light->FirstChildElement("Falloff");

	Light * newLight;
	m_lights->Allocate(&newLight);
	switch (type->IntAttribute("type"))
	{
	case 0:
	{
		newLight->SetType(LightProperties::LIGHT_TYPE_SUN);
		break;
	}
	case 1:
	{
		newLight->SetType(LightProperties::LIGHT_TYPE_POINT);
		break;
	}
	case 2:
	{
		newLight->SetType(LightProperties::LIGHT_TYPE_SPOT);
		break;
	}
	default:
		break;
	}
	// \todo Set falloff setting
	newLight->SetColor(
		color->FloatAttribute("r"),
		color->FloatAttribute("g"),
		color->FloatAttribute("b"),
		color->FloatAttribute("a"));
	newLight->SetPosition(
		position->FloatAttribute("x"),
		position->FloatAttribute("y"),
		position->FloatAttribute("z"));
	newLight->SetDirection(
		direction->FloatAttribute("x"),
		direction->FloatAttribute("y"),
		direction->FloatAttribute("z"));
	newLight->SetAngle(angle->FloatAttribute("a"));
	// \todo Set radius
	return TRUE;
}
