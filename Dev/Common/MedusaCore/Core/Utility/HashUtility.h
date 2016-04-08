#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Compile/Type.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;



namespace HashUtility
{

	namespace Private
	{
		template<typename T>
		inline intp Hash_Imp(T val,Compile::Bool2Type<true>)
		{
			return (intp)val;
		}

		template<typename T>
		inline intp Hash_Imp(T val,Compile::Bool2Type<false>)
		{
			intp result=0;
			intp* p=(intp*)&val;
			FOR_EACH_SIZE(i,sizeof(T)/sizeof(intp))
			{
				result^=p[i];
			}
			return result;
		}
	}

	int32 HashString(const char* str);
	int32 HashIntArray(const int* buffer,size_t size,int32 initialValue=0);
	int64 HashIntArray64(const int* buffer,size_t size,int64 initialValue=0);
	int32 HashStringJenkins(const char* buffer,size_t length,int32 initialValue=0);
	int64 HashStringJenkins64(const char* buffer,size_t length,int64 initialValue=0);

	template<typename T,size_t size>
	inline intp Hash(T (&buffer)[size])
	{
		intp result=0;
		intp* p=(intp*)buffer;
		FOR_EACH_SIZE(i,size*sizeof(T)/sizeof(intp))
		{
			result^=p[i];
		}
		return result;
	}

	template<typename T>
	inline intp Hash(T val)
	{
		return HashUtility::Private::Hash_Imp(val,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

}

MEDUSA_END;