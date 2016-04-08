#pragma once
#include "Core/Collection/IDictionary.h"
#include "Core/Collection/List.h"
#include "Core/Collection/HashHelper.h"
#include "Core/Collection/STLPort.h"

MEDUSA_BEGIN;

template<typename TKey,typename TValue,typename TKeyCompare=DefaultCompare<TKey> >
class SortedDictionary:public IDictionary<TKey,TValue,std::pair<TKey,TValue>,TKeyCompare>
{
public:
	typedef IDictionary<TKey,TValue,std::pair<TKey,TValue>,TKeyCompare> BaseType;
	typedef typename BaseType::KeyValuePairType KeyValuePairType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TKeyParameterType TKeyParameterType;
	typedef typename BaseType::TValueParameterType TValueParameterType;
	typedef typename BaseType::TValueReferenceType TValueReferenceType;
	typedef typename BaseType::TValueConstReturnType TValueConstReturnType;
	typedef typename BaseType::TValuePointerType TValuePointerType;
	typedef typename BaseType::TKeyPointerType TKeyPointerType;
	typedef typename BaseType::TKeyConstPointerType TKeyConstPointerType;
	typedef typename BaseType::TValueConstPointerType TValueConstPointerType;

	typedef std::map<TKey,TValue,TKeyCompare> MapType;
	typedef SortedDictionary<TKey,TValue,TKeyCompare> SelfType;

	const static SelfType Empty;
public:
	SortedDictionary(size_t capacity=4)
	{
		
	}
	virtual ~SortedDictionary()
	{

	}

#pragma region IEnumerable
protected:

	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}

#pragma endregion IEnumerable

#pragma region ICollection
public:
	virtual bool IsLinear() const{return false;}
	virtual size_t GetCount() const{return mItems.size();}
	virtual TConstPointerType GetItems() const{MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}
	virtual TPointerType GetItems() {MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}

	virtual bool Contains(TParameterType val)const
	{
		return ContainsKey(val.first);
	}
	virtual size_t CopyTo(KeyValuePairType* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT((size_t)arraySize>=mItems.size(),"arraySize should >= size");
		size_t index=0;
		FOR_EACH_COLLECTION_STL(i,mItems)
		{
			outArray[index++]=KeyValuePairType(i->first,i->second);
		}
		return index;	
	}

	
#pragma endregion ICollection

#pragma region IDictionary

public:
	//virtual KeyCollectionType& GetKeys()const=0;
	//virtual ValueCollectionType& GetValues()const=0;

	virtual void Add(TParameterType val)
	{
		mItems.insert(val);
		this->mCount=mItems.size();
	}

	virtual bool TryAdd(TParameterType val)
	{
		std::pair<typename MapType::iterator, bool> ret=mItems.insert(val);
		if(ret.second)
		{
			this->mCount=mItems.size();
			return true;
		}

		return false;
	}

	virtual bool Remove(TParameterType val)
	{
		return RemoveKey(val.first);
	}
	virtual void Clear()
	{
		mItems.clear();
		this->mCount=mItems.size();
	}

	virtual bool ContainsKey(TKeyParameterType key)const
	{
		return mItems.find(key)!=mItems.end();
	}
	virtual bool ContainsValue(TValueParameterType value)const
	{
		FOR_EACH_COLLECTION_STL(i,mItems)
		{
			if (i->second==value)
			{
				return true;
			}
		}

		return false;
	}

	virtual TValueReferenceType GetValue(TKeyParameterType key)
	{
		typename MapType::iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			return i->second;
		}

		MEDUSA_ASSERT_FAILED("cannot find entry");
		return i->second;
	}
	virtual TValueConstReturnType GetValue(TKeyParameterType key)const
	{
		typename MapType::const_iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			return i->second;
		}

		MEDUSA_ASSERT_FAILED("cannot find entry");
		return i->second;
	}

	virtual void SetValue(TKeyParameterType key,TValueParameterType value)
	{
		mItems[key]=value;
	}

	virtual TValuePointerType TryGetValue(TKeyParameterType key)
	{
		typename MapType::iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			return (TValuePointerType)&(i->second);
		}
		return NULL;
	}

	virtual TValueConstPointerType TryGetValue(TKeyParameterType key)const
	{
		typename MapType::const_iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			return (TValueConstPointerType)&(i->second);
		}
		return NULL;
	}

	virtual TValue TryGetValueWithFailed(TKeyParameterType key,TValueParameterType failedReturn)const
	{
		typename MapType::const_iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			return i->second;
		}
		return failedReturn;
	}


	virtual TKeyPointerType TryGetKey(TValueParameterType value)
	{
		FOR_EACH_COLLECTION_STL(i,mItems)
		{
			if (i->second==value)
			{
				return (TKeyPointerType)&(i->first);
			}
		}
		return NULL;
	}

	virtual TKeyConstPointerType TryGetKey(TValueParameterType value)const
	{
		FOR_EACH_COLLECTION_STL(i,mItems)
		{
			if (i->second==value)
			{
				return (TKeyConstPointerType)&(i->first);
			}
		}
		return NULL;
	}

	virtual void Add(TKeyParameterType key,TValueParameterType value)
	{
		mItems.insert(KeyValuePairType(key,value));

		this->mCount=mItems.size();
	}

	virtual bool TryAdd(TKeyParameterType key,TValueParameterType value)
	{
		std::pair<typename MapType::iterator, bool> ret=mItems.insert(KeyValuePairType(key,value));
		if(ret.second)
		{
			this->mCount=mItems.size();
			return true;
		}
		return false;
	}

	virtual bool RemoveKey(TKeyParameterType key)
	{
		typename MapType::iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			mItems.erase(i);
			this->mCount=mItems.size();

			return true;
		}
		return false;

	}

	virtual TValue RemoveKeyWithValueReturned(TKeyParameterType key,TValueParameterType failedReturn)
	{
		typename MapType::iterator i=mItems.find(key);
		if (i!=mItems.end())
		{
			TValue result=i->second;
			mItems.erase(i);
			this->mCount=mItems.size();

			return result;
		}
		return failedReturn;
	}


	virtual bool RemoveValue(TValueParameterType value)
	{
		FOR_EACH_COLLECTION_STL(i,mItems)
		{
			if (i->second==value)
			{
				mItems.erase(i);
				this->mCount=mItems.size();

				return true;
			}
		}
		return false;
	}

#pragma endregion IDictionary
public:
	MapType& GetSTLItems(){return mItems;}
	const MapType& GetSTLItems()const{return mItems;}

private:
	MapType mItems;
};


template<typename TKey,typename TValue,typename TKeyCompare>
WEAK_MULTIPLE_DEFINE const SortedDictionary<TKey,TValue,TKeyCompare> SortedDictionary<TKey,TValue,TKeyCompare>::Empty;

MEDUSA_END;