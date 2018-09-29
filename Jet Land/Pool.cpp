#include "Pool.h"

template <class T>
Pool<T>::Pool() : Pool(0)
{
}

template<class T>
Pool<T>::Pool(size_t size) :
	m_size(size),
	m_pool(size)
{
}

template<class T>
Pool<T>::~Pool()
{
	for (auto it = m_pool.begin(); it != m_pool.end(); ++it)
	{
		it->Terminate();
	}
}

template<class T>
VOID Pool<T>::Allocate(T ** object)
{
	for (auto elem = m_pool.begin(); elem != m_pool.end(); ++elem)
	{
		if (!elem->IsActive())
		{
			elem->Initialize();
			*object = &(*elem);
			return;
		}
	}
}

template<class T>
VOID Pool<T>::Release(T * object)
{
	if (object->IsActive())
	{
		object->Terminate();
	}
}

template<class T>
VOID Pool<T>::Resize(size_t new_size)
{
	m_size = new_size;
	m_pool.resize(new_size);
}

template<class T>
VOID Pool<T>::Clear()
{
	m_pool.clear();
}