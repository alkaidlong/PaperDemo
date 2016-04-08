#pragma once
#include "Core/Collection/ISet.h"
#include "Core/Collection/List.h"
#include "Core/Collection/HashHelper.h"

MEDUSA_BEGIN;

template<typename T,typename THashCoder=DefaultHashCoder<T>,typename TCompare=EqualCompare<T> >
class HashSet:public ISet<T,TCompare>
{
public:
	typedef HashSet<T,THashCoder,TCompare> SelfType;

	typedef typename SelfType::TReturnType TReturnType;
	typedef typename SelfType::TParameterType TParameterType;
	typedef typename SelfType::TReferenceType TReferenceType;
	typedef typename SelfType::TConstReturnType TConstReturnType;
	typedef typename SelfType::TPointerType TPointerType;
	typedef typename SelfType::TConstPointerType TConstPointerType;


private:
	struct Entry
	{
		intp HashCode;    // Lower 31 bits of hash code, -1 if unused  
		intp Next;        // Index of next entry, -1 if last
		T Value;
	};
public:
	HashSet(size_t capacity=0)
	{
		Initialize(capacity);
	}

	HashSet(const HashSet& dict)
	{
		Initialize(dict.GetCount());

		FOR_EACH_COLLECTION(i,dict)
		{
			Add(*i);
		}

	}
	virtual ~HashSet()
	{
		SAFE_DELETE_ARRAY(mEntries);
		SAFE_DELETE_ARRAY(mBuckets);
		mAddedCount=0;
		this->mCount=0;
	}

#pragma region IEnumerable
public:
	class HashSetEnumerator:public IEnumerator<TReturnType>
	{
		friend class HashSet<T,THashCoder,TCompare>;
		explicit HashSetEnumerator(Entry* entries,size_t count):mEntries(entries),mAddedCount(count),mIndex(0),mCurrent(NULL){}

	public:
		virtual TReturnType Current(){return mCurrent->Value; }
		TReturnType operator*(){return mCurrent->Value; }

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

	class ConstHashSetEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class HashSet<T,THashCoder,TCompare>;
		explicit ConstHashSetEnumerator(const Entry* entries,size_t count):mEntries(entries),mAddedCount(count),mIndex(0),mCurrent(NULL){}

	public:
		virtual TConstReturnType Current(){return mCurrent->Value; }
		TConstReturnType operator*(){return mCurrent->Value; }


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
	ConstHashSetEnumerator GetEnumerator()const{return ConstHashSetEnumerator(mEntries,mAddedCount);}
	HashSetEnumerator GetEnumerator(){return HashSetEnumerator(mEntries,mAddedCount);}
protected:

	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstHashSetEnumerator(mEntries,mAddedCount);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new HashSetEnumerator(mEntries,mAddedCount);}

#pragma endregion IEnumerable

#pragma region ICollection
public:
	virtual bool IsLinear() const{return false;}
	virtual TConstPointerType GetItems() const{MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}
	virtual TPointerType GetItems() {MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}

	virtual bool Contains(TParameterType val)const
	{
		return FindEntry(val)>=0;
	}

	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(mEntries);
		intp index=0;
		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if(entry.HashCode>=0)
			{
				outArray[index++]=entry.Value;
			}
		}
		return index;
	}


#pragma endregion ICollection

#pragma region ISet

public:

	virtual void Clear()
	{
		mFreeList=-1;
		mAddedCount=0;
		mFreeCount=0;
		this->mCount=0;

		Memory::Set(mBuckets,(char)-1,mSize);

	}

	template<typename T2>
	bool ContainsOther(T2 otherValue,intp hashCode)const
	{
		return FindEntryByOther(otherValue,hashCode)>=0;
	}

	virtual void Add(TParameterType value)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			Resize();
		}

		intp hashCode= ( THashCoder::GetHashCode(value))&0x7FFFFFFF;
		intp targetBucket=hashCode%mSize;
		for (intp i=mBuckets[(size_t)targetBucket];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TCompare::Compare(value,mEntries[(size_t)i].Value)==0))
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
		entry.Value=value;
		mBuckets[(size_t)targetBucket]=index;
		++this->mCount;
	}

	virtual bool TryAdd(TParameterType value)
	{
		if (mBuckets==NULL||mEntries==NULL)
		{
			Resize();
		}
		intp hashCode= ( THashCoder::GetHashCode(value))&0x7FFFFFFF;
		intp targetBucket=hashCode%mSize;
		for (intp i=mBuckets[(size_t)targetBucket];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TCompare::Compare(value,mEntries[(size_t)i].Value)==0))
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
		entry.Value=value;
		mBuckets[(size_t)targetBucket]=index;
		++this->mCount;
		return true;
	}


	virtual bool Remove(TParameterType val)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode= ( THashCoder::GetHashCode(val))&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TCompare::Compare(val,mEntries[(size_t)i].Value)==0))
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


	template<typename T2>
	bool RemoveOtherValue(T2 otherValue,intp otherHashCode)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode= ( otherHashCode)&0x7FFFFFFF;
		intp bucket=hashCode%mSize;
		intp last=-1;
		for (intp i=mBuckets[(size_t)bucket];i>=0;last=i,i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TCompare::Compare(otherValue,mEntries[(size_t)i].Value)==0))
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

	// Modifies the current object to contain all elements that are present in itself, the specified collection, or both.
	virtual void UnionWith(const ICollection<T>& other)
	{
		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			TryAdd(*i);
		}
	}

	//Modifies the current object to contain only elements that are present in that object and in the specified collection.
	virtual void IntersectWith(const ICollection<T>& other)
	{
		if (other.IsEmpty())
		{
			Clear();
			return;
		}

		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if (entry.HashCode>=0)
			{
				if (other.Contains(entry.Value))
				{
					Remove(entry.Value);
				}
			}
		}
	}

	// Removes all elements in the specified collection from the current object.
	virtual void ExceptWith(const ICollection<T>& other)
	{
		RETURN_IF_EMPTY(other);
		if ((SelfType*)&other==this)
		{
			Clear();
			return;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			Remove(*i);
		}

	}


	//Modifies the current object to contain only elements that are present either in that object or in the specified collection, but not both.
	virtual void SymmetricExceptWith(const ICollection<T>& other)
	{
		if (this->IsEmpty())
		{
			UnionWith(other);
		}
		else if ((SelfType*)&other==this)
		{
			Clear();
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i,other)
			{
				if(!Remove(*i))
				{
					TryAdd(*i);
				}
			}

		}
	}

	//Determines whether a object is a subset of the specified collection.
	virtual bool IsSubsetOf(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return true;
		}

		if (this->mCount>other.GetCount())
		{
			return false;
		}

		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if (entry.HashCode>=0)
			{
				if (!other.Contains(entry.Value))
				{
					return false;
				}
			}
		}

		return true;


	}

	//Determines whether a object is a superset of the specified collection.
	virtual bool IsSupersetOf(const ICollection<T>& other)const
	{
		RETURN_TRUE_IF_EMPTY(other);

		if (this->mCount<other.GetCount())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			if(!Contains(*i))
			{
				return false;
			}
		}

		return true;
	}

	//Determines whether a object is a proper superset of the specified collection.
	virtual bool IsProperSupersetOf(const ICollection<T>& other)const
	{
		RETURN_TRUE_IF_EMPTY(other);
		if (this->mCount<other.GetCount())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			if(!Contains(*i))
			{
				return false;
			}
		}

		return this->mCount>other.GetCount();
	}

	//Determines whether a object is a proper superset of the specified collection.
	virtual bool IsProperSubsetOf(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return true;
		}

		if (this->mCount>other.GetCount())
		{
			return false;
		}

		FOR_EACH_SIZE(i,mSize)
		{
			const Entry& entry=mEntries[i];
			if (entry.HashCode>=0)
			{
				if (!other.Contains(entry.Value))
				{
					return false;
				}
			}
		}

		return this->mCount<other.GetCount();
	}

	//true if the object and other share at least one common element; otherwise, false.
	virtual bool IsOverlaps(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			if(Contains(*i))
			{
				return true;
			}
		}
		return false;
	}

	//Determines whether a object and the specified collection contain the same elements.
	virtual bool Equals(const ICollection<T>& other)const
	{
		if (this->mCount!=other.GetCount())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i,other)
		{
			if(!Contains(*i))
			{
				return false;
			}
		}

		return true;
	}



#pragma endregion ISet

private:
	intp FindEntry(TParameterType val)const
	{
		if(mEntries==NULL||mBuckets==NULL)
		{
			return -1;
		}

		intp hashCode= ( THashCoder::GetHashCode(val))&0x7FFFFFFF;
		for (intp i=mBuckets[hashCode%mSize];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&( TCompare::Compare(val,mEntries[(size_t)i].Value)==0))
			{
				return i;
			}
		}

		return -1;
	}

	template<typename T2>
	intp FindEntryByOther(T2 otherValue,intp hashCode)const
	{
		if(mEntries==NULL||mBuckets==NULL)
		{
			return -1;
		}

		hashCode= ( hashCode)&0x7FFFFFFF;
		for (intp i=mBuckets[hashCode%mSize];i>=0;i=mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode==hashCode&&TCompare::Compare(mEntries[(size_t)i].Value,otherValue)==0)
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

		ResizeEntriesHelper(Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());

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
	size_t mFreeCount;
	size_t mAddedCount;

};

MEDUSA_END;