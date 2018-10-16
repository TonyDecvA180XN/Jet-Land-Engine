#pragma once



#include <vector>
#include <algorithm>

template <class T>
class Pool
{
public:
	Pool();
	Pool(size_t size);
	~Pool();

	VOID Allocate(T ** object);
	VOID Release(T * object);

	auto Begin() { return m_pool.begin(); };
	auto End() { return m_pool.end(); };

	VOID Resize(size_t new_size);
	size_t GetSize() { return m_size; };

	VOID Clear();

	static BOOL FindObject(Pool<T> * pool, std::string name);
	static T * UseObject(Pool<T> * pool, std::string name);
private:
	std::vector<T> m_pool;
	size_t m_size;
};


#include "Pool.cpp"