#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/String/TStringRef.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;


//HeapString StringRef::operator+( const StringRef& self,const HeapString& str ) const
//{
//	return HeapString(self)+str;
//
//}

template<typename T>
THeapString<T> TStringRef<T>::operator+( const TStringRef<T>& inString ) const
{
	return THeapString<T>(mBuffer)+inString;
}


template<typename T>
THeapString<T> Medusa::TStringRef<T>::operator+( const char c ) const
{
	return THeapString<T>(mBuffer)+c;

}

template<typename T>
THeapString<T> Medusa::TStringRef<T>::SubString(size_t index,size_t length)const
{
	if (IsNull()||length==0)
	{
		return THeapString<T>::Empty;
	}
	THeapString<T> result(mBuffer+index,length+1);
	result[length]=0;
	result.ForceSetLength(length);
	return result;
}
MEDUSA_END;