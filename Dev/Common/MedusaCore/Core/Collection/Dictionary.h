#pragma once
#include "Core/Collection/IDictionary.h"
#include "Core/Collection/List.h"
#include "Core/Collection/HashHelper.h"

MEDUSA_BEGIN;

template<typename TKey,typename TValue,typename THashCoder=DefaultHashCoder<TKey>,typename TKeyCompare=DefaultCompare<TKey>,typename TValueCompare=EqualCompare<TValue> >
class Dictionary:public IDictionary<TKey,TValue,KeyValuePair<TKey,TValue>,TKeyCompare,TValueCompare>
{
public:
	typedef Dictionary<TKey,TValue,THashCoder,TKeyCompare,TValueCompare> SelfType;
    
	typedef typename SelfType::KeyValuePairType KeyValuePairType;
	typedef typename SelfType::TReturnType TReturnType;
	typedef typename SelfType::TConstReturnType TConstReturnType;
	typedef typename SelfType::TPointerType TPointerType;
	typedef typename SelfType::TConstPointerType TConstPointerType;
	typedef typename SelfType::TParameterType TParameterType;
	typedef typename SelfType::TKeyParameterType TKeyParameterType;
	typedef typename SelfType::TValueParameterType TValueParameterType;
	typedef typename SelfType::TValueReferenceType TValueReferenceType;
	typedef typename SelfType::TValueConstReturnType TValueConstReturnType;
	typedef typename SelfType::TValuePointerType TValuePointerType;
	typedef typename SelfType::TKeyPointerType TKeyPointerType;
	typedef typename SelfType::TKeyConstPointerType TKeyConstPointerType;
	typedef typename SelfType::TValueConstPointerType TValueConstPointerType;
    
    const static SelfType Empty;
private:
	struct Entry
	{
		intp HashCode;    // Lower 31 bits of hash code, -1 if unused  
		intp Next;        // Index of next entry, -1 if last
		KeyValuePairType Pair;
	};
public:
	Dictionary(size_t capacity=0)
	{
		Initialize(capacity);
	}

	Dictionary(const Dictionary& dict)
	{
		Initialize(dict.GetCount());

		FOR_EACH_COLLECTION(i,dict)
		{
			Add((*i).Key,(*i).Value);
		}

	}
	virtual ~Dictionary()
	{
		SAFE_DELETE_ARRAY(mEntries);
		SAFE_DELETE_ARRAY(mBuckets);
		mAddedCount=0;
		this->mCount=0;
	}

#pragma region IEnumerable
public:
	class DictionaryEnumerator:public IEnumerator<TReturnType>
	{
		friend class Dictionary<TKey,TValue,THashCoder,TKeyCompare,TValueCompare>;
		explicit DictionaryEnumerator(Entry* entries,size_t count):mEntries(entries),mAddedCount(count),mIndex(0),mCurrent(NULL){}

	public:
		virtual TReturnType Current(){return mCurrent->Pair; }
		TReturnType operator*(){return mCurrent->Pair; }

		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_NULL(mEntries);
			while (mIndex < mAddedCount)
			{ 
				if (mEntries[mIndex].HashCode >= 0)
				{  
					mCurrent=&(mEntries[mIndex]);
					mIndex++;  
					return true;  
				} 
				mIndex++;  
			} 

			mIndex = mAddedCount + 1; 
			mCurrent = NULL;
			
			return false; 
		}
		virtual void Reset()
		{
			mCurrent=NULL;
			mIndex=0;
		}
	protected:
		Entry* mEntries;
		size_t mIndex;
		size_t mAddedCount;
		Entry* mCurrent;
	};

	class ConstDictionaryEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class Dictionary<TKey,TValue,THashCoder,TKeyCompare,TValueCompare>;
		explicit ConstDictionaryEnumerator(const Entry* entries,size_t count):mEntries(entries),mAddedCount(count),mIndex(0),mCurrent(NULL){}

	public:
		virtual TConstReturnType Current(){return mCurrent->Pair; }
		TConstReturnType operator*(){return mCurrent->Pair; }


		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_NULL(mEntries);
			while (mIndex < mAddedCount)
			{ 
				if (mEntries[mIndex].HashCode >= 0)
				{  
					mCurrent=&(mEntries[mIndex]);
					mIndex++;  
					return true;  
				} 
				mIndex++;  
			} 

			mIndex = mAddedCount + 1; 
			mCurrent = NULL;

			return false; 
		}
		virtual void Reset()
		{
			mCurrent=NULL;
			mIndex=0;
		}
	protected:
		const Entry* mEntries;
		size_t mIndex;
		size_t mAddedCount;
		const Entry* mCurrent;
	};
	public:
		ConstDictionaryEnumerator GetEnumerator()const{return ConstDictionaryEnumerator(mEntries,mAddedCount);}
		DictionaryEnumerator GetEnumerator(){return DictionaryEnumerator(mEntries,mAddedCount);}
protected:

	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstDictionaryEnumerator(mEntries,mAddedCount);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new DictionaryEnumerator(mEntries,mAddedCount);}

#pragma endregion IEnumerable

#pragma region ICollection
public:
	virtual bool IsLinear() const{return false;}
	virtual TConstPointerType GetItems() const{MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}
	virtual TPointerType GetItems() {MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}

	virtual bool Contains(TParameterType val)const
	{
		return ContainsKey(val.Key);
	}
	virtual size_t CopyTo(KeyValuePairType* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(mEntries);
		intp index=0;
		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if(entry.HashCode>=0)
			{
				outArray[index++]=entry.Pair;
			}
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
		Add(val.Key,val.Value);
	}

	virtual bool TryAdd(TParameterType val)
	{
		return TryAdd(val.Key,val.Value);
	}

	virtual bool Remove(TParameterType val)
	{
		return RemoveKey(val.Key);
	}
	virtual void Clear()
	{
		mFreeList=-1;
		mAddedCount=0;
		mFreeCount=0;
		this->mCount=0;

		Memory::Set(mBuckets,(char)-1,mSize);

	}

	virtual bool ContainsKey(TKeyParameterType key)const
	{
		return FindEntry(key)>=0;
	}

	template<typename TKey2>
	bool ContainsOtherKey(TKey2 key,intp hashCode)const
	{
		return FindEntryByOtherKey(key,hashCode)>=0;
	}


	virtual bool ContainsValue(TValueParameterType value)const
	{
		RETURN_FALSE_IF_NULL(mEntries);
		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if(TValueCompare::Compare(entry.Pair.Value,value)==0)
			{
				return true;
			}
		}

		return false;
	}

	virtual TValueReferenceType GetValue(TKeyParameterType key)
	{
		intp i = FindEntry(key);  
		MEDUSA_ASSERT(i>=0,"cannot find entry");
		Entry& entry=mEntries[(size_t)i];

		return entry.Pair.Value;
	}
	virtual TValueConstReturnType GetValue(TKeyParameterType key)const
	{
		intp i = FindEntry(key);  
		MEDUSA_ASSERT(i>=0,"cannot find entry");
		const Entry& entry=mEntries[(size_t)i];

		return entry.Pair.Value;
	}

	virtual void SetValue(TKeyParameterType key,TValueParameterType value)
	{
		intp i = FindEntry(key);
		if (i>=0)
		{
			mEntries[(size_t)i].Pair.Value=value;
		}
		else
		{
			Add(key,value);
		}
	}

	virtual TValuePointerType TryGetValue(TKeyParameterType key)
	{
		 intp i = FindEntry(key);  
		 if (i>=0)
		 {
			 return (TValuePointerType)&(mEntries[(size_t)i].Pair.Value);
		 }
		 return NULL;
	}

	template<typename TKey2>
	TValuePointerType TryGetValueByOtherKey(TKey2 key,intp hashCode)
	{
		intp i = FindEntryByOtherKey(key,hashCode);  
		if (i>=0)
		{
			return (TValuePointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return NULL;
	}

	virtual TValueConstPointerType TryGetValue(TKeyParameterType key)const
	{
		intp i = FindEntry(key);  
		if (i>=0)
		{
			return (TValueConstPointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return NULL;
	}

	template<typename TKey2>
	TValueConstPointerType TryGetValueByOtherKey(TKey2 key,intp hashCode)const
	{
		intp i = FindEntryByOtherKey(key,hashCode);  
		if (i>=0)
		{
			return (TValueConstPointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return NULL;
	}


	virtual TValue TryGetValueWithFailed(TKeyParameterType key,TValueParameterType failedReturn)const
	{
		intp i = FindEntry(key);  
		if (i>=0)
		{
			return mEntries[(size_t)i].Pair.Value;
		}
		return failedReturn;
	}

	template<typename TKey2>
	TValue TryGetValueWithFailedByOtherKey(TKey2 key,intp hashCode,TValueParameterType failedReturn)const
	{
		intp i = FindEntryByOtherKey(key,hashCode);
		if (i>=0)
		{
			return mEntries[(size_t)i].Pair.Value;
		}
		return failedReturn;
	}

	virtual TKeyPointerType TryGetKey(TValueParameterType value)
	{
		RETURN_NULL_IF_NULL(mEntries);
		FOR_EACH_SIZE(i,mSize)
		{
			Entry& entry=mEntries[i];
			if(TValueCompare::Compare(entry.Pair.Value,value)==0)
			{
				return (TKeyPointerType)&(entry.Pair.Key);
			}
		}

		return NULL;
	}

	virtual TKeyConstPointerType TryGetKey(TValueParameterType value)const
	{
		RETURN_NULL_IF_NULL(mEntries);

		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if(TValueCompare::Compare(entry.Pair.Value,value)==0)
			{
				return (TKeyConstPointerType)&(entry.Pair.Key);
			}
		}

		return NULL;
	}

	virtual void Add(TKeyParameterType key,TValueParameterType value)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			Resize();
		}

		intp hashCode= ( THashCoder::GetHashCode(key))&0x7FFFFFFF;
		intp targetBucket=hashCode%mSize;
		for (intp i=mBuckets[(size_t)targetBucket];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				//
				MEDUSA_ASSERT_FAILED("duplicate add");
				return;
			}
		}

		intp index=0;
		if (mFreeCount>0)
		{
			//add in free list
			index=mFreeList;
			mFreeList=mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount==mSize)
			{
				Resize();
				targetBucket=hashCode%mSize;
			}
			index=mAddedCount;
			++mAddedCount;
		}
		Entry& entry=mEntries[(size_t)index];
		entry.HashCode=hashCode;
		entry.Next=mBuckets[(size_t)targetBucket];
		entry.Pair.Key=key;
		entry.Pair.Value=value;
		mBuckets[(size_t)targetBucket]=index;
		++this->mCount;
	}

	virtual bool TryAdd(TKeyParameterType key,TValueParameterType value)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			Resize();
		}
		intp hashCode= ( THashCoder::GetHashCode(key))&0x7FFFFFFF;
		intp targetBucket=hashCode%mSize;
		for (intp i=mBuckets[(size_t)targetBucket];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				return false;
			}
		}

		intp index=0;
		if (mFreeCount>0)
		{
			//add in free list
			index=mFreeList;
			mFreeList=mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount==mSize)
			{
				Resize();
				targetBucket=hashCode%mSize;
			}
			index=mAddedCount;
			++mAddedCount;
		}
		Entry& entry=mEntries[(size_t)index];
		entry.HashCode=hashCode;
		entry.Next=mBuckets[(size_t)targetBucket];
		entry.Pair.Key=key;
		entry.Pair.Value=value;
		mBuckets[(size_t)targetBucket]=index;
		++this->mCount;
		return true;
	}


	virtual bool RemoveKey(TKeyParameterType key)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode= ( THashCoder::GetHashCode(key))&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				if (last<0)
				{
					mBuckets[(size_t)bucket]=mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next=mEntries[(size_t)i].Next;
				}

				Entry& entry=mEntries[(size_t)i];
				entry.HashCode=-1;
				entry.Next=mFreeList;

				mFreeList=i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}

	virtual TValue RemoveKeyWithValueReturned(TKeyParameterType key,TValueParameterType failedReturn)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			return failedReturn;
		}

		intp hashCode= ( THashCoder::GetHashCode(key))&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				if (last<0)
				{
					mBuckets[(size_t)bucket]=mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next=mEntries[(size_t)i].Next;
				}

				Entry& entry=mEntries[(size_t)i];
				entry.HashCode=-1;
				entry.Next=mFreeList;

				mFreeList=i;
				mFreeCount++;
				--this->mCount;
				return entry.Pair.Value;
			}
		}

		return failedReturn;
	}



	template<typename TKey2>
	bool RemoveOtherKey(TKey2 key,intp otherHashCode)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode= ( otherHashCode)&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				if (last<0)
				{
					mBuckets[(size_t)bucket]=mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next=mEntries[(size_t)i].Next;
				}

				Entry& entry=mEntries[(size_t)i];
				entry.HashCode=-1;
				entry.Next=mFreeList;

				mFreeList=i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}

	template<typename TKey2>
	TValue RemoveOtherKeyWithValueReturned(TKey2 key,intp otherHashCode,TValueParameterType failedReturn)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			return failedReturn;
		}
		intp hashCode= ( otherHashCode)&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				if (last<0)
				{
					mBuckets[(size_t)bucket]=mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next=mEntries[(size_t)i].Next;
				}

				Entry& entry=mEntries[(size_t)i];
				entry.HashCode=-1;
				entry.Next=mFreeList;

				mFreeList=i;
				mFreeCount++;
				--this->mCount;
				return entry.Pair.Value;
			}
		}

		return failedReturn;
	}

	virtual bool RemoveValue(TValueParameterType value)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if(TValueCompare::Compare(entry.Pair.Value,value)==0)
			{
				return RemoveKey(entry.Pair.Key);
			}
		}

		return false;
	}

#pragma endregion IDictionary

private:
	intp FindEntry(TKeyParameterType key)const
	{
		if(mEntries==NULL||mBuckets==NULL)
		{
			return -1;
		}

		intp hashCode= ( THashCoder::GetHashCode(key))&0x7FFFFFFF;
		for (intp i=mBuckets[hashCode%mSize];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				return i;
			}
		}

		return -1;
	}

	template<typename TKey2>
	intp FindEntryByOtherKey(TKey2 key,intp hashCode)const
	{
		if(mEntries==NULL||mBuckets==NULL)
		{
			return -1;
		}

		hashCode= ( hashCode)&0x7FFFFFFF;
		for (intp i=mBuckets[hashCode%mSize];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TKeyCompare::Compare(key,mEntries[(size_t)i].Pair.Key)==0))
			{
				return i;
			}
		}

		return -1;
	}

	void Initialize(size_t capacity)
	{
		if (capacity>0)
		{
			mSize=HashHelper::GetPrime(capacity);
			mBuckets=new intp[mSize];
			Memory::Set(mBuckets,(char)-1,mSize);
			mEntries=new Entry[mSize];
		}
		else
		{
			mSize=0;
			mBuckets=NULL;
			mEntries=NULL;
		}

		mAddedCount=0;
		mFreeList=-1;
		mFreeCount=0;
		this->mCount=0;
	}

	void Resize()
	{
		mSize=HashHelper::GetPrime(mAddedCount<<1);
		Memory::Realloc(mBuckets,mSize);
		Memory::Set(mBuckets,(char)-1,mSize);

		ResizeEntriesHelper(Compile::Bool2Type<Compile::TypeTraits<TKey>::IsPOD&&Compile::TypeTraits<TValue>::IsPOD>());

		for (size_t i=0;i<mAddedCount;i++)
		{
			intp bucket=mEntries[(size_t)i].HashCode%mSize;
			mEntries[(size_t)i].Next=mBuckets[(size_t)bucket];
			mBuckets[(size_t)bucket]=i;
		}
	}

	void ResizeEntriesHelper(Compile::Bool2Type<true>)
	{
		Memory::Realloc(mEntries,mSize);
	}

	void ResizeEntriesHelper(Compile::Bool2Type<false>)
	{
		Entry* newEntries=new Entry[mSize];
		Memory::Copy(newEntries,mEntries,mAddedCount);
		SAFE_DELETE_ARRAY(mEntries);
		mEntries=newEntries;
	}
private:
	intp* mBuckets;
	Entry* mEntries;

	size_t mSize;
	intp mFreeList;
	intp mFreeCount;
	size_t mAddedCount;


};

template<typename TKey,typename TValue,typename THashCoder,typename TKeyCompare,typename TValueCompare>
WEAK_MULTIPLE_DEFINE const Dictionary<TKey,TValue,THashCoder,TKeyCompare,TValueCompare> Dictionary<TKey,TValue,THashCoder,TKeyCompare,TValueCompare>::Empty;

MEDUSA_END;