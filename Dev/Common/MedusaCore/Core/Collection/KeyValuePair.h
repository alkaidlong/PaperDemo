#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Utility/HashUtility.h"



MEDUSA_BEGIN;

template<typename TKey,typename TValue>
struct KeyValuePair
{
	typedef TKey KeyType;
	typedef TValue ValueType;

	typedef typename Compile::TypeTraits<TKey>::ParameterType TKeyParameterType;
	typedef typename Compile::TypeTraits<TValue>::ParameterType TValueParameterType;
	TKey Key;
	TValue Value;

	KeyValuePair():Key(),Value(){}
	KeyValuePair(TKeyParameterType key,TValueParameterType value):Key(key),Value(value){}

	KeyValuePair& operator=(const KeyValuePair& pair){Key=pair.Key;Value=pair.Value;return *this;}
	bool operator==(const KeyValuePair& pair)const{return Key==pair.Key&&Value==pair.Value;}
	bool operator<(const KeyValuePair& pair)const{return Key<pair.Key&&Value<pair.Value;}
	intp GetHashCode()const{return HashUtility::Hash(Key)^HashUtility::Hash(Value);}

};

MEDUSA_END;