#include "Material.h"
#include "TinyXML/tinyxml2.h"

Material::Material()
= default;

Material::~Material()
= default;

DirectX::XMVECTOR Material::GetDiffuseXM()
{
	return DirectX::XMVectorSet(m_diffuse.x, m_diffuse.y, m_diffuse.z, 1.0f);
}

VOID Material::SetDiffuseXM(DirectX::XMVECTOR diffuse)
{
	DirectX::XMStoreFloat4(&m_diffuse, diffuse);
	PoolObject::Update();
}

VOID Material::GetDiffuse(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_diffuse.x;
	g = m_diffuse.y;
	b = m_diffuse.z;
}

VOID Material::SetDiffuse(FLOAT r, FLOAT g, FLOAT b)
{
	m_diffuse.x = r;
	m_diffuse.y = g;
	m_diffuse.z = b;
	PoolObject::Update();
}

DirectX::XMVECTOR Material::GetAmbientXM()
{
	return DirectX::XMVectorSet(m_ambient.x, m_ambient.y, m_ambient.z, 1.0f);
}

VOID Material::SetAmbientXM(DirectX::XMVECTOR ambient)
{
	DirectX::XMStoreFloat4(&m_ambient, ambient);
	PoolObject::Update();
}

VOID Material::GetAmbient(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_ambient.x;
	g = m_ambient.y;
	b = m_ambient.z;
}

VOID Material::SetAmbient(FLOAT r, FLOAT g, FLOAT b)
{
	m_ambient.x = r;
	m_ambient.y = g;
	m_ambient.z = b;
	PoolObject::Update();
}

DirectX::XMVECTOR Material::GetSpecularXM()
{
	return DirectX::XMVectorSet(m_specular.x, m_specular.y, m_specular.z, 1.0f);
}

VOID Material::SetSpecularXM(DirectX::XMVECTOR specular)
{
	DirectX::XMStoreFloat4(&m_specular, specular);
	PoolObject::Update();
}

VOID Material::GetSpecular(FLOAT &r, FLOAT &g, FLOAT &b)
{
	r = m_specular.x;
	g = m_specular.y;
	b = m_specular.z;
}

VOID Material::SetSpecular(FLOAT r, FLOAT g, FLOAT b)
{
	m_specular.x = r;
	m_specular.y = g;
	m_specular.z = b;
	PoolObject::Update();
}

FLOAT Material::GåtShininess()
{
	return m_shininess;
}

VOID Material::SetShininess(FLOAT shininess)
{
	m_shininess = shininess;
	PoolObject::Update();
}

FLOAT Material::GåtTransparency()
{
	return m_transparency;
}

VOID Material::SetTransparency(FLOAT transparency)
{
	m_transparency = transparency;
	PoolObject::Update();
}

FLOAT Material::GåtMirror()
{
	return m_mirror;
}

VOID Material::SetMirror(FLOAT mirror)
{
	m_mirror = mirror;
	PoolObject::Update();
}

FLOAT Material::GåtIOR()
{
	return m_IOR;
}

VOID Material::SetIOR(FLOAT ior)
{
	m_IOR = ior;
	PoolObject::Update();
}

Material::MaterialBuffer Material::GenerateBuffer()
{
	MaterialBuffer buffer;
	buffer.mDiffuse = m_diffuse;
	buffer.mAmbient = m_ambient;
	buffer.mSpecular = m_specular;
	buffer.mShininess = m_shininess;
	buffer.mTransparency = m_transparency;
	buffer.mMirror = m_mirror;
	buffer.mIOR = m_IOR;
	return buffer;
}
