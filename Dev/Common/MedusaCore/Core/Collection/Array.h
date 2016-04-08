#pragma once

#include "Core/Collection/ICollection.h"
#include "Core/Collection/STLPort.h"
#include "Core/Memory/Memory.h"


MEDUSA_BEGIN;

template<typename T, size_t TSize,typename TCompare=DefaultCompare<T> >
class Array:public ICollection<T>
{
	typedef Array<T,TSize,TCompare> SelfType;

	typedef IEnumerable<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

public:
	const static size_t Size=TSize;

	Array()
	{
		this->mCount=TSize;
	}

	Array(const Array& items)
	{
		Memory::CopyConstructIterator(mItems,items.GetItems(),items.GetCount());
		this->mCount=TSize;
	}

	template<typename T1, size_t TSize1>
	Array(const Array<T1,TSize1>& items)
	{
		MEDUSA_COMPILE_ASSERT(TSize1>=TSize,TOO_BIG_SIZE);
		Memory::CopyConstructIterator(mItems,items.GetItems(),items.GetCount());
	}

	bool operator==(const Array& items)const
	{
		return Memory::Compare<T,TCompare>(mItems,items.GetItems(),items.GetCount())==0;
	}
	bool operator<(const Array& items)const
	{
		return Memory::Compare<T,TCompare>(mItems,items.GetItems(),items.GetCount())<0;
	}

	Array& operator=(const Array& items)
	{
		Memory::CopyConstructIterator(mItems,items.GetItems(),items.GetCount());
		return *this;
	}

	template<typename T1, size_t TSize1>
	Array& operator=(const Array<T1,TSize1>& items)
	{
		MEDUSA_COMPILE_ASSERT(TSize1>=TSize,TOO_BIG_SIZE);
		Memory::CopyConstructIterator(mItems,items.GetItems(),items.GetCount());
		return *this;
	}

	template<typename T1>
	Array(const ICollection<T1>& items)
	{
		MEDUSA_ASSERT_IF(items.GetCount()<=TSize,"");
		this->mCount=TSize;

		if (items.IsLinear())
		{
			Memory::CopyConstructIterator(mItems,items.GetItems(),items.GetCount());
		}
		else
		{
			size_t index=0;
			FOR_EACH_COLLECTION(i,items)
			{
				Set(index++,*i);
			}
		}
	}

public:
	TReferenceType operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index<TSize,"");
		return mItems[index];
	}

	TConstReturnType operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index<TSize,"");
		return mItems[index];
	}

	TConstReturnType Get(size_t index)const
	{
		MEDUSA_ASSERT_IF(index<TSize,"");
		return mItems[index];
	}

	void Set(size_t index,TParameterType val)
	{
		MEDUSA_ASSERT_IF(index<TSize,"");
		mItems[index]=val;
	}

#pragma region IEnumerable interface
public:
	class ArrayEnumerator:public IEnumerator<TReturnType>
	{
		friend class Array<T,TSize,TCompare>;
		explicit ArrayEnumerator(T* items,size_t size):mItems(items),mSize(size),mIndex(-1){}

	public:
		virtual TReturnType Current(){return mItems[mIndex];}
		TReturnType operator*(){return mItems[mIndex];}


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(intp)mSize;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		T* mItems;
		size_t mSize;
		intp mIndex;
	};

	class ConstArrayEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class Array<T,TSize,TCompare>;
		explicit ConstArrayEnumerator(const T* items,size_t size):mItems(items),mSize(size),mIndex(-1){}

	public:
		virtual TConstReturnType Current(){return mItems[mIndex];}
		TConstReturnType operator*(){return mItems[mIndex];}


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(intp)mSize;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		const T* mItems;
		size_t mSize;
		intp mIndex;
	};
	public:
		ConstArrayEnumerator GetEnumerator()const{return ConstArrayEnumerator(mItems,TSize);}
		ArrayEnumerator GetEnumerator(){return ArrayEnumerator(mItems,TSize);}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstArrayEnumerator(mItems,TSize);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new ArrayEnumerator(mItems,TSize);}

#pragma endregion IEnumerable interface

#pragma region ICollection interface
public:
	virtual bool IsLinear() const{return true;}
	virtual TConstPointerType GetItems() const { return (T*)mItems; }
	virtual TPointerType GetItems(){return (T*)mItems;}

	virtual bool Contains(TParameterType val)const
	{
		return IndexOf(0,TSize-1,val)>=0;
	}
	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT(arraySize>=TSize,"TOO_BIG_SIZE");
		Memory::CopyConstructIterator(outArray,mItems,TSize);
		return TSize;
	}

	

#pragma endregion ICollection interface

public:
	void ClearZero()
	{
		Memory::SetZero(mItems,TSize);
	}

	virtual void Add(TParameterType val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();
	}
	virtual bool Remove(TParameterType val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();

		return true;
	}

	virtual void Clear()
	{
		
	}

	virtual intp IndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		FOR_EACH_SIZE_BEGIN_END(i,srcBegin,srcEnd)
		{
			if ( TCompare::Compare(mItems[i],val)==0)
			{
				return (intp)i;
			}
		}


		return -1;
	}

	virtual intp LastIndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		FOR_EACH_SIZE_END_BEGIN(i,srcEnd-1,srcBegin-1)
		{
			if ( TCompare::Compare(mItems[i],val)==0)
			{
				return (intp)i;
			}
		}

		return -1;
	}

	virtual void SetAll(size_t srcBegin,size_t srcEnd,TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		Memory::Set(mItems+srcBegin,val,srcEnd-srcBegin);
	}

	virtual void SetAll(TParameterType val)
	{
		Memory::Set(mItems,val,TSize);
	}

	virtual void ReplaceAll(size_t srcBegin,size_t srcEnd,TParameterType oldValue,TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		FOR_EACH_SIZE_BEGIN_END(i,srcBegin,srcEnd)
		{
			if ( TCompare::Compare(mItems[i],oldValue)==0)
			{
				mItems[i]=newValue;
			}
		}
	}



	virtual void ReplaceFirst(size_t srcBegin,size_t srcEnd,TParameterType oldValue,TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		FOR_EACH_SIZE_BEGIN_END(i,srcBegin,srcEnd)
		{
			if ( TCompare::Compare(mItems[i],oldValue)==0)
			{
				mItems[i]=newValue;
				break;
			}
		}

	}

	virtual void ReplaceLast(size_t srcBegin,size_t srcEnd,TParameterType oldValue,TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		FOR_EACH_SIZE_END_BEGIN(i,srcEnd-1,srcBegin-1)
		{
			if ( TCompare::Compare(mItems[i],oldValue)==0)
			{
				mItems[i]=newValue;
				break;
			}
		}

	}

	virtual void Reverse(size_t srcBegin,size_t srcEnd)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize,"");

		while(srcBegin<srcEnd)
		{
			TParameterType temp=mItems[srcBegin];
			mItems[srcBegin]=mItems[srcEnd];
			mItems[srcEnd]=temp;
			++srcBegin;
			--srcEnd;
		}
	}

protected:
	T mItems[TSize];

};

MEDUSA_END;