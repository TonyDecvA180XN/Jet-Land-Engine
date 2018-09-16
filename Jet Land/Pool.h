#pragma once

#include "IncluderW.h"
#include "IncluderSTD.h"
#include <vector>


template <class T>
class Pool
{
public:
	Pool();
	Pool(size_t size);
	~Pool();

	VOID Allocate(T ** object);
	VOID Release(T * object);

	VOID Resize(size_t new_size);
	size_t GetSize() { return m_size; };
private:
	std::vector<T> m_pool;
	size_t m_size;
};
