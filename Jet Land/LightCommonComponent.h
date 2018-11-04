#pragma once

#include "Globals.h"
#include "Utils.h"

#include "Pool.h"
#include "LightSource.h"

class LightCommonComponent
{
public:
	LightCommonComponent();
	~LightCommonComponent();

	VOID Create(ID3D11Device * device);
	VOID Destroy();

	VOID Update(ID3D11DeviceContext * device_context);

	ID3D11Buffer ** GetBufferLP();
	Pool<Light> * GetPool();

private:
	Pool<Light> m_lights;
	ID3D11Buffer * m_lb;
};

