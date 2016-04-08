#pragma once

#include "Core/Collection/Enumerator.h"
#include "Core/Compile/TypeTraits.h"

/************************************************************************/
/* 
I decide to use interface with lots of virtual member functions because:
1.Support interface advantages, such as we can limit interface functions
2.We can afford virtual call cost because it's so little. Here's the data:
	Normal call: 1000000000 times, cost:63ms, average=0.000001ms==1ns
	Virtual call: 1000000000 times, cost:374ms, average=0.000004ms==4ns
It means that although virtual will bring 1 extra pointer addressing and may prevent inline optimization, it cost least!
You'll rarely loop 100 million times to do stuffs!
On my opinion, ensure program reliability always win! And there's an old saying that:
Premature/Excessive optimization is a nightmare!
In the future, I will provide profiling tools to look deeply into program's performance. 
At that time, we'll all have a clear understanding about where's the program's performance bottleneck.
Now, let's rock!

Jack 2011-12-15
*/
/************************************************************************/

MEDUSA_BEGIN;

template<typename T>
struct IEnumerable
{
public:
	typedef typename Compile::TypeTraits<T>::ConstType TConstItemType;
	typedef typename Compile::TypeTraits<T>::PointerType TPointerType;
	typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	typedef typename Compile::TypeTraits<T>::ConstReferenceType TConstReturnType;
	typedef typename Compile::TypeTraits<T>::ReferenceType TReturnType;
	typedef typename Compile::TypeTraits<T>::ConstPointerType TConstPointerType;

	Enumerator<TConstReturnType> GetEnumeratorVirtual()const{return Enumerator<TConstReturnType>(GetEnumeratorVirtualHelper());}
	Enumerator<TReturnType> GetEnumeratorVirtual(){return Enumerator<TReturnType>(GetEnumeratorVirtualHelper());}


protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const=0;
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper()=0;

	IEnumerable(){}
	virtual ~IEnumerable(){}
};

MEDUSA_END;