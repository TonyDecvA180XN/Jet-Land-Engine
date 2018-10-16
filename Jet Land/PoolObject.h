#pragma once



class PoolObject
{
public:
	PoolObject() : m_isActive(FALSE), m_name() {};
	PoolObject(std::string name) : m_isActive(FALSE), m_name(name) {};

	virtual VOID Initialize() { this->Activate(TRUE); };
	virtual VOID Terminate() { this->Activate(FALSE); };

	BOOL IsActive() { return this->m_isActive; };

	std::string       GetName() { return m_name; };
	VOID              SetName(std::string name) { m_name = name; };

protected:
	VOID Activate(BOOL state) { this->m_isActive = state; }

private:
	BOOL m_isActive;
	std::string m_name;
};

