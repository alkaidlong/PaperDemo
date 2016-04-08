#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Ptr/NotNullPtr.h"


MEDUSA_BEGIN;

namespace Pattern
{
	//DO NOT copy LazyStrongPtr to another LazyStrongPtr
	//DO NOT delete LazyStrongPtr
	//DO NOT put into collections because it cannot be copied
	template<typename T>
	class LazyStrongPtr
	{
	public:
		explicit LazyStrongPtr(T* ptr=NULL):mPtr(ptr){}

		template<typename T2>
		explicit LazyStrongPtr(T2* ptr):mPtr(ptr){}

		LazyStrongPtr(const LazyStrongPtr& ptr){mPtr=ptr.mPtr;}

		template<typename T2>
		LazyStrongPtr(const LazyStrongPtr<T2>& ptr){mPtr=ptr.mPtr;}


		~LazyStrongPtr(){Release();}
		T& operator*()const{return *mPtr;}
		T* operator->()const{return mPtr;}
		operator T*()const{return mPtr;}

		T* ForcePtr();
		T& ForceReference();

		T* Ptr()const{return mPtr;}
		T& Reference()const{return *mPtr;}

		template<typename T2>
		operator Pattern::NotNullPtr<T2>()const{return Pattern::NotNullPtr<T2>(mPtr);}

		LazyStrongPtr& operator=(T* ptr){Release();mPtr=ptr;return *this;}
		LazyStrongPtr& operator=(const LazyStrongPtr& ptr){Release();mPtr=ptr.mPtr;return *this;}


		template<typename T2>
		LazyStrongPtr& operator=(T2* ptr){Release();mPtr=ptr;return *this;}

		template<typename T2>
		LazyStrongPtr& operator=(const LazyStrongPtr<T2>& ptr){Release();mPtr=ptr.mPtr;return *this;}

		void Alloc();
		void Release();
		
		void ForceSet(T* ptr){mPtr=ptr;}
	protected:
		void* operator new (size_t t);
		void  operator delete(void *ptr);
	private:
		T* mPtr;
	};

	

}
MEDUSA_END;