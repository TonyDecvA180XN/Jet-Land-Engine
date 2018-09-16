#pragma once

#include "IncluderW.h"

class PoolObject
{
public:
	PoolObject() : m_isActive(FALSE) {};

	virtual BOOL Initialize() = 0;
	virtual VOID Terminate() = 0;

	BOOL IsActive() { return this->m_isActive; };

protected:
	VOID Activate(BOOL state) { this->m_isActive = state; }

private:
	BOOL m_isActive;
};

