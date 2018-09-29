#pragma once



class PoolObject
{
public:
	PoolObject() : m_isActive(FALSE) {};

	virtual VOID Initialize() { this->Activate(TRUE); };
	virtual VOID Terminate() { this->Activate(FALSE); };

	BOOL IsActive() { return this->m_isActive; };

protected:
	VOID Activate(BOOL state) { this->m_isActive = state; }

private:
	BOOL m_isActive;
};

