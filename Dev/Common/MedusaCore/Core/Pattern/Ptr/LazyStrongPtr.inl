#pragma once
#include "Core/Pattern/Ptr/LazyStrongPtr.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename T>
	T* LazyStrongPtr<T>::ForcePtr()
	{
		Alloc();
		return mPtr;
	}

	template<typename T>
	T& LazyStrongPtr<T>::ForceReference()
	{
		Alloc();
		return *mPtr;
	}


	template<typename T>
	void LazyStrongPtr<T>::Alloc()
	{
		if (mPtr==NULL)
		{
			mPtr=new T();
		}
	}

	template<typename T>
	void LazyStrongPtr<T>::Release()
	{
		SAFE_DELETE(mPtr);
	}
}
MEDUSA_END;