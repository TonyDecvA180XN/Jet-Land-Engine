#include "Loader.h"
#include "OBJ_Loader.h"
#include "JMH_Loader.h"
#include "DDSTextureLoader.h"
#include "TinyXML/tinyxml2.h"


Mesh * Loader::LoadMesh(Pool<Mesh>* pool, std::string name, std::string filename)
{
	if (pool->HaveObject(name))
	{
		return pool->FindObject(name);
	}
	else
	{
		Mesh * newMesh;
		pool->Allocate(name, &newMesh);


		// --------------------------------- Mesh Loading ---------------------
		if (filename.size() > 4)
		{
			std::string extOBJ(".obj"), extJMH(".jmh");
			if (std::equal(extJMH.rbegin(), extJMH.rend(), filename.rbegin())) // check if filename ends with jmh extension
			{
				LoadMeshJMHFromFile(filename, &newMesh->m_vFormat,
					&newMesh->m_vertexArray, &newMesh->m_vertexCount,
					&newMesh->m_vertexSize, &newMesh->m_indexArray,
					&newMesh->m_indexCount);
			}
			if (std::equal(extOBJ.rbegin(), extOBJ.rend(), filename.rbegin())) // check if filename ends with obj extension
			{
				LoadMeshOBJFromFile(filename, &newMesh->m_vFormat,
					&newMesh->m_vertexArray, &newMesh->m_vertexCount,
					&newMesh->m_vertexSize, &newMesh->m_indexArray,
					&newMesh->m_indexCount);
			}
		}

		return newMesh;
	}
}

Texture * Loader::LoadTexture(Pool<Texture>* pool, std::string name, std::string filename, ID3D11Device * device)
{
	if (pool->HaveObject(name))
	{
		return pool->FindObject(name);
	}
	else
	{
		Texture * newTexture;
		pool->Allocate(name, &newTexture);

		// -------------------------------- Texture Loading -------------------
		DirectX::CreateDDSTextureFromFile(device,
			std::wstring(filename.begin(), filename.end()).c_str(),
			NULL, &newTexture->m_srv);

		return newTexture;
	}
}

Material * Loader::LoadMaterial(Pool<Material>* pool, std::string name, std::string filename)
{
	if (pool->HaveObject(name))
	{
		return pool->FindObject(name);
	}
	else
	{
		Material * newMaterial;
		pool->Allocate(name, &newMaterial);

		// ------------------------------- Material Loading -------------------
		tinyxml2::XMLDocument materialFile;
		materialFile.LoadFile(filename.c_str());

		tinyxml2::XMLElement * materials = materialFile.FirstChildElement("Materials");
		tinyxml2::XMLElement * materialBlock = materials->FirstChildElement("Material");
		while (materialBlock != NULL)
		{
			if (materialBlock->Attribute("name", name.c_str()))
			{
				break;
			}
			materialBlock = materialBlock->NextSiblingElement();
		}
		tinyxml2::XMLElement * diffuse = materialBlock->FirstChildElement("Diffuse");
		tinyxml2::XMLElement * ambient = materialBlock->FirstChildElement("Ambient");
		tinyxml2::XMLElement * specular = materialBlock->FirstChildElement("Specular");
		tinyxml2::XMLElement * roughness = materialBlock->FirstChildElement("Roughness");
		tinyxml2::XMLElement * transparency = materialBlock->FirstChildElement("Transparency");
		tinyxml2::XMLElement * mirror = materialBlock->FirstChildElement("Mirror");
		tinyxml2::XMLElement * ior = materialBlock->FirstChildElement("IOR");

		newMaterial->m_diffuse = DirectX::XMFLOAT4(diffuse->FloatAttribute("r"), diffuse->FloatAttribute("g"), diffuse->FloatAttribute("b"), 1.0f);
		newMaterial->m_ambient = DirectX::XMFLOAT4(ambient->FloatAttribute("r"), ambient->FloatAttribute("g"), ambient->FloatAttribute("b"), 1.0f);
		newMaterial->m_specular = DirectX::XMFLOAT4(specular->FloatAttribute("r"), specular->FloatAttribute("g"), specular->FloatAttribute("b"), 1.0f);
		newMaterial->m_roughness = roughness->FloatAttribute("v");
		newMaterial->m_transparency = transparency->FloatAttribute("v");
		newMaterial->m_mirror = mirror->FloatAttribute("v");
		newMaterial->m_IOR = ior->FloatAttribute("v");

		return newMaterial;
	}

}

Light * Loader::LoadLight(LightCommonComponent * lights, std::string name, std::string filename)
{
	if (lights->GetPool()->HaveObject(name))
	{
		return lights->GetPool()->FindObject(name);
	}
	else
	{
		Light * newLight;
		lights->GetPool()->Allocate(name, &newLight);

		// ------------------------------- Light Loading ----------------------
		tinyxml2::XMLDocument lightFile;
		lightFile.LoadFile(filename.c_str());
		tinyxml2::XMLElement * lights = lightFile.FirstChildElement("Lights");
		tinyxml2::XMLElement * iLight = lights->FirstChildElement("Light");
		while (iLight != NULL)
		{
			if (iLight->Attribute("name", name.c_str()))
			{
				break;
			}
			iLight = iLight->NextSiblingElement();
		}
		tinyxml2::XMLElement * color = iLight->FirstChildElement("Color");
		tinyxml2::XMLElement * position = iLight->FirstChildElement("Position");
		tinyxml2::XMLElement * direction = iLight->FirstChildElement("Direction");
		tinyxml2::XMLElement * radius = iLight->FirstChildElement("Radius");
		tinyxml2::XMLElement * angle = iLight->FirstChildElement("Angle");
		tinyxml2::XMLElement * type = iLight->FirstChildElement("Type");
		tinyxml2::XMLElement * falloff = iLight->FirstChildElement("Falloff");

		newLight->m_type = LightProperties::LightType(type->IntAttribute("type"));
		newLight->m_falloff = LightProperties::LightFalloff(falloff->IntAttribute("falloff"));
		newLight->m_color = DirectX::XMFLOAT4(color->FloatAttribute("r"), color->FloatAttribute("g"), color->FloatAttribute("b"), color->FloatAttribute("a"));
		newLight->m_position = DirectX::XMFLOAT3(position->FloatAttribute("x"), position->FloatAttribute("y"), position->FloatAttribute("z"));
		newLight->m_direction = DirectX::XMFLOAT3(direction->FloatAttribute("x"), direction->FloatAttribute("y"), direction->FloatAttribute("z"));
		newLight->m_angle = angle->FloatAttribute("a");
		newLight->m_radius = radius->FloatAttribute("r");

		return newLight;
	}
}

CompiledShader * Loader::LoadShader(Pool<CompiledShader>* pool, std::string name, std::string filename)
{
	if (pool->HaveObject(name))
	{
		return pool->FindObject(name);
	}
	else
	{
		CompiledShader * newShader;
		pool->Allocate(name, &newShader);

		// -------------------------------- Shader Loading --------------------
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		newShader->m_size = in.tellg();
		in.close();
		std::ifstream input(filename, std::ifstream::binary | std::istream::in);
		if (input.fail()) { return NULL; }
		newShader->m_buffer = new uint8_t[newShader->m_size];
		if (!newShader->m_buffer) { return NULL; }
		input.read((char *)(newShader->m_buffer), newShader->m_size);
		input.close();

		return newShader;
	}
}

VOID Loader::LoadLocation(ID3D11Device * device, std::string filename, Pool<StaticMesh>* static_meshes, Pool<Mesh>* meshes, Pool<Texture>* textures,
	LightCommonComponent * lights, Pool<Material>* materials, Camera * camera, Pool<CompiledShader> * shaders)
{
	tinyxml2::XMLDocument locationFile;
	locationFile.LoadFile(filename.c_str());
	tinyxml2::XMLElement * location = locationFile.FirstChildElement("Location");
	tinyxml2::XMLElement * worldSettings = location->FirstChildElement("World");
	// \todo take world settings

	tinyxml2::XMLElement * layout = location->FirstChildElement("Layout");

	// --------------------------- Lights ----------------------------------------
	tinyxml2::XMLElement * lightsList = layout->FirstChildElement("Lights");
	tinyxml2::XMLElement * iLight = lightsList->FirstChildElement();
	while (iLight != NULL)
	{
		Loader::LoadLight(lights, iLight->Attribute("name"), iLight->Attribute("filename"));
		iLight = iLight->NextSiblingElement();
	}

	// -------------------------- Static Meshes --------------------------------
	tinyxml2::XMLElement * meshesList = layout->FirstChildElement("Meshes");
	tinyxml2::XMLElement * iStaticMesh = meshesList->FirstChildElement("StaticMesh");
	while (iStaticMesh != NULL)
	{
		std::string meshName = iStaticMesh->Attribute("name");
		if (!static_meshes->HaveObject(meshName))
		{
			StaticMesh * newMesh;
			static_meshes->Allocate(meshName, &newMesh);

			// -------------------------------- Static Mesh Loading -----------
			ID3D11DeviceContext * device_context;
			device->GetImmediateContext(&device_context);
			tinyxml2::XMLElement * model = iStaticMesh->FirstChildElement("Model");
			tinyxml2::XMLElement * material = iStaticMesh->FirstChildElement("Material");
			tinyxml2::XMLElement * texture = iStaticMesh->FirstChildElement("Texture");
			tinyxml2::XMLElement * vs = iStaticMesh->FirstChildElement("VertexShader");
			tinyxml2::XMLElement * ps = iStaticMesh->FirstChildElement("PixelShader");
			tinyxml2::XMLElement * pos = iStaticMesh->FirstChildElement("Position");
			tinyxml2::XMLElement * rot = iStaticMesh->FirstChildElement("Rotation");
			tinyxml2::XMLElement * scale = iStaticMesh->FirstChildElement("Scale");

			Mesh * pMesh = Loader::LoadMesh(meshes, model->Attribute("name"), model->Attribute("filename"));
			Material * pMaterial = Loader::LoadMaterial(materials, material->Attribute("name"), material->Attribute("filename"));
			Texture * pTexture = (texture != NULL ? Loader::LoadTexture(textures, texture->Attribute("name"), texture->Attribute("filename"), device) : NULL);
			CompiledShader * pVS = Loader::LoadShader(shaders, vs->Attribute("name"), vs->Attribute("filename"));
			CompiledShader * pPS = Loader::LoadShader(shaders, ps->Attribute("name"), ps->Attribute("filename"));

			newMesh->Initiate(device, device_context, lights, camera, pMesh, pMaterial, pTexture, pVS, pPS);

			newMesh->SetPosition(pos->FloatAttribute("x", 0.0f), pos->FloatAttribute("y", 0.0f), pos->FloatAttribute("z", 0.0f));
			newMesh->SetRotation(rot->FloatAttribute("x", 0.0f), rot->FloatAttribute("y", 0.0f), rot->FloatAttribute("z", 0.0f));
			newMesh->SetScaling(scale->FloatAttribute("x", 0.0f), scale->FloatAttribute("y", 0.0f), scale->FloatAttribute("z", 0.0f));
		}
		iStaticMesh = iStaticMesh->NextSiblingElement();
	}

	return;
}
