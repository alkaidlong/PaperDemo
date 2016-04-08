#pragma once

#include "MedusaCorePreCompiled.h"

#include "Core/Collection/IEnumerable.h"
#include "Core/Collection/ICollection.h"
#include "Core/Collection/KeyValuePair.h"
#include "Core//Compile/TypeTraits.h"

MEDUSA_BEGIN;

template<typename TKey,typename TValue,typename TKeyValuePair,typename TKeyCompare=DefaultCompare<TKey>,typename TValueCompare=DefaultCompare<TValue> >
struct IDictionary:public ICollection<TKeyValuePair>
{
public:
    typedef typename ICollection<TKeyValuePair>::TParameterType TParameterType;
public:
	IDictionary(){}
	virtual ~IDictionary(){}
public:
	typedef TKey KeyType;
	typedef TValue ValueType;
	typedef TKeyValuePair KeyValuePairType;

	typedef typename Compile::TypeTraits<TValue>::ReferenceType TValueReferenceType;
	typedef typename Compile::TypeTraits<TValue>::ConstReturnType TValueConstReturnType;

	typedef typename Compile::TypeTraits<TValue>::PointerType TValuePointerType;
	typedef typename Compile::TypeTraits<TValue>::ConstPointerType TValueConstPointerType;

	typedef typename Compile::TypeTraits<TKey>::ParameterType TKeyParameterType;
	typedef typename Compile::TypeTraits<TValue>::ParameterType TValueParameterType;

	typedef typename Compile::TypeTraits<TKey>::ReferenceType TKeyReferenceType;
	typedef typename Compile::TypeTraits<TKey>::PointerType TKeyPointerType;
	typedef typename Compile::TypeTraits<TKey>::ConstPointerType TKeyConstPointerType;

	typedef ICollection<TKey> KeyCollectionType;
	typedef ICollection<TValue> ValueCollectionType;
public:
	TValueConstReturnType operator[](TKeyParameterType key)const{return GetValue(key);}
	TValueReferenceType operator[](TKeyParameterType key){return GetValue(key);}
public:
	//virtual KeyCollectionType& GetKeys()const=0;
	//virtual ValueCollectionType& GetValues()const=0;
	virtual bool ContainsKey(TKeyParameterType key)const=0;
	virtual bool ContainsValue(TValueParameterType value)const=0;

	virtual TValueReferenceType GetValue(TKeyParameterType key)=0;
	virtual TValueConstReturnType GetValue(TKeyParameterType key)const=0;
	virtual void SetValue(TKeyParameterType key,TValueParameterType value)=0;

	virtual TValuePointerType TryGetValue(TKeyParameterType key)=0;
	virtual TKeyPointerType TryGetKey(TValueParameterType value)=0;

	virtual TValueConstPointerType TryGetValue(TKeyParameterType key)const=0;
	virtual TKeyConstPointerType TryGetKey(TValueParameterType value)const=0;

	virtual TValue TryGetValueWithFailed(TKeyParameterType key,TValueParameterType failedReturn)const=0;

	virtual void Add(TKeyParameterType key,TValueParameterType value)=0;
	virtual bool TryAdd(TKeyParameterType key,TValueParameterType value)=0;


	virtual bool RemoveKey(TKeyParameterType key)=0;
	virtual bool RemoveValue(TValueParameterType value)=0;


	virtual TValue RemoveKeyWithValueReturned(TKeyParameterType key,TValueParameterType failedReturn)=0;

	virtual void Add(TParameterType val)=0;
	virtual bool TryAdd(TParameterType val)=0;
	virtual bool Remove(TParameterType val)=0;
	virtual void Clear()=0;
};

MEDUSA_END;