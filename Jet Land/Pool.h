#pragma once

template <class T>
class Pool
{
public:
	Pool();
	Pool(size_t size);
	~Pool();

	VOID Allocate(std::string name, T ** object);
	VOID Release(T * object);
	VOID Release(std::string name);

	
	VOID Resize(size_t new_size);
	size_t GetSize() { return m_size; };

	VOID Clear();

	BOOL HaveObject(std::string name);
	T * FindObject(std::string name);

private:
	friend class LightCommonComponent;
	friend class GraphicsManager;

	T * GetItem(UINT i);
	BOOL AnyUpdates();

private:
	std::vector<T> m_pool;
	size_t m_size;
};

#include "Pool.cpp"