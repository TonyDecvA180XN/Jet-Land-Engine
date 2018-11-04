#pragma once

class PoolObject
{
public:
	PoolObject() : m_isActive(FALSE), m_name(), m_isUpdated(TRUE) {};

	virtual VOID Initialize(std::string name) { this->Activate(TRUE); m_name = name; };
	virtual VOID Terminate() { if (this->IsActive()) { this->Activate(FALSE); m_name = ""; } };

	BOOL IsActive() { return this->m_isActive; };

	VOID Update() { m_isUpdated = TRUE; }

	BOOL CheckForUpdates() {
		if (m_isUpdated) { m_isUpdated = FALSE; return TRUE; }
		else return FALSE;
	}

	std::string GetName() { return m_name; };
private:
	VOID Activate(BOOL state) { this->m_isActive = state; }

private:
	BOOL m_isActive;
	BOOL m_isUpdated;
	std::string m_name;
};

