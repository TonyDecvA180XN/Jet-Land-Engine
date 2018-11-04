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
VOID Pool<T>::Allocate(std::string name, T ** object)
{
	for (auto elem = m_pool.begin(); elem != m_pool.end(); ++elem)
	{
		if (!elem->IsActive())
		{
			elem->Initialize(name);
			*object = &(*elem);
			return;
		}
	}
}

template<class T>
VOID Pool<T>::Release(T * object)
{
	assert((uintptr_t)object >= (uintptr_t)this->m_pool.front &&
		(uintptr_t)object < (uintptr_t)this->m_pool.end);
	object->Terminate();
}

template<class T>
VOID Pool<T>::Release(std::string name)
{
	if (this->HaveObject(name))
	{
		this->FindObject(name)->Terminate();
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

template<class T>
BOOL Pool<T>::HaveObject(std::string name)
{
	return std::find_if(
		this->m_pool.begin(),
		this->m_pool.end(),
		[name](T instance) -> BOOL { return instance.GetName() == name; })
		!= m_pool.end();
}

template<class T>
T * Pool<T>::FindObject(std::string name)
{
	return &*std::find_if(
		this->m_pool.begin(),
		this->m_pool.end(),
		[name](T instance) -> BOOL { return instance.GetName() == name; });
}

template<class T>
T * Pool<T>::GetItem(UINT i)
{
	return &m_pool[i];
}

template<class T>
BOOL Pool<T>::AnyUpdates()
{
	for (auto o : this->m_pool)
	{
		if (o.CheckForUpdates())
		{
			return TRUE;
		}
	}
	return FALSE;
}
