#pragma once
#include "Core/Collection/ISortedList.h"
#include "Core/Collection/STLPort.h"
#include "Core/Algorithm/Algorithm.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/MathHeader.h"


MEDUSA_BEGIN;


template<typename T,typename TCompare=DefaultCompare<T>, typename TSorter=DefaultCompare<T> >
class SortedList:public ISortedList<T>
{
	typedef SortedList<T,TCompare,TSorter> SelfType;

public:
    
    
	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;
    
	using ISortedList<T>::IndexOf;
	using ISortedList<T>::LastIndexOf;
	using ISortedList<T>::Add;
	using ISortedList<T>::RemoveAt;
	using ISortedList<T>::RemoveAll;
    
    //using typename IEnumerable<T>::TConstPointerType;
   // using typename IEnumerable<T>::TPointerType;
   // using typename IEnumerable<T>::TParameterType;
   // using typename IEnumerable<T>::TReturnType;
   // using typename IEnumerable<T>::TConstReturnType;
   // using typename IEnumerable<T>::TReferenceType;

	const static SelfType Empty;
public:
	explicit SortedList(size_t size=0)
	{
		mSize=size;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;
	}


	SortedList(const SortedList& items)
	{
		mSize=items.GetCount();
		this->mCount=mSize;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;

		Memory::CopyConstructIterator(this->mItems,items.GetItems(),mSize);
	}



	SortedList& operator=(const SortedList<T,TCompare,TSorter>& items)
	{
		Clear();
		size_t newCount=items.GetCount();
		if (mSize>=newCount)
		{
			Memory::CopyConstructIterator(this->mItems,items.GetItems(),newCount);
			this->mCount=newCount;
			ReleaseExtraSize();
		}
		else
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,newCount);
			Resize(newSize);
			Memory::CopyConstructIterator(this->mItems,items.GetItems(),newCount);
			this->mCount=newCount;
		}

		return *this;
	}

	template<typename T1,typename TCompare1>
	SortedList& operator=(const SortedList<T1,TCompare1>& items)
	{
		Clear();
		size_t newCount=items.GetCount();
		if (mSize>=newCount)
		{
			Memory::CopyConstructIterator(this->mItems,items.GetItems(),newCount);
			this->mCount=newCount;
			ReleaseExtraSize();
		}
		else
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,newCount);
			Resize(newSize);
			Memory::CopyConstructIterator(this->mItems,items.GetItems(),newCount);
			this->mCount=newCount;
		}


		return *this;
	}

	virtual ~SortedList(void)
	{
		Memory::DestoryRange(this->mItems,this->mCount);
		SAFE_FREE(this->mItems);
	}


public:

#pragma region IEnumerable interface
public:

	class SortedListEnumerator:public IEnumerator<TReturnType>
	{
		friend class SortedList<T,TCompare,TSorter>;
		explicit SortedListEnumerator(T* items,size_t count):mItems(items),mCount(count),mIndex(-1){}

	public:
		virtual TReturnType Current(){return this->mItems[mIndex];}
		TReturnType operator*(){return this->mItems[mIndex];}


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(int)this->mCount;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		T* mItems;
		size_t mCount;
		int mIndex;
	};

	class ConstSortedListEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class SortedList<T,TCompare,TSorter>;
		explicit ConstSortedListEnumerator(const T* items,size_t count):mItems(items),mCount(count),mIndex(-1){}

	public:
		virtual TConstReturnType Current(){return this->mItems[mIndex];}
		TConstReturnType operator*(){return this->mItems[mIndex];}


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(int)this->mCount;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		const T* mItems;
		size_t mCount;
		int mIndex;
	};
	public:
		ConstSortedListEnumerator GetEnumerator()const{return ConstSortedListEnumerator(this->mItems,this->mCount);}
		SortedListEnumerator GetEnumerator(){return SortedListEnumerator(this->mItems,this->mCount);}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstSortedListEnumerator(this->mItems,this->mCount);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new SortedListEnumerator(this->mItems,this->mCount);}


#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	virtual bool IsLinear() const{return true;}
	virtual TConstPointerType GetItems() const { return this->mItems; }
	virtual TPointerType GetItems() { return this->mItems; }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(this->mItems);
		size_t count=Math::Min(this->mCount,(size_t)arraySize);
		Memory::CopyConstructIterator(outArray,this->mItems,count);
		return count;
	}

	virtual bool Contains(TParameterType val)const{RETURN_FALSE_IF_ZERO(this->mCount);return IndexOf(0,this->mCount-1,val)>=0;}

#pragma endregion ICollection interface

#pragma region ISortedList interface

	virtual intp IndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<=this->mCount,"");

		intp firstIndex= Algorithm::BinarySearchFirst<T,TSorter>(this->mItems,val,srcBegin,srcEnd);
		if (firstIndex<0)
		{
			return firstIndex;
		}

		while (firstIndex<(intp)this->mCount)
		{
			if (TCompare::Compare(this->mItems[firstIndex],val)==0)
			{
				return firstIndex;
			}
			++firstIndex;
		}

		return -1;
	}


	virtual intp LastIndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<=this->mCount,"");
		intp lastIndex= Algorithm::BinarySearchLast<T,TSorter>(this->mItems,val,srcBegin,srcEnd);
		if (lastIndex<0)
		{
			return lastIndex;
		}

		while (lastIndex>=0)
		{
			if (TCompare::Compare(this->mItems[lastIndex],val)==0)
			{
				return lastIndex;
			}
			--lastIndex;
		}

		return -1;
	}


	virtual void RemoveAt(size_t index)
	{
		MEDUSA_ASSERT_IF(index<this->mCount,"");
		Memory::Destory(this->mItems+index);
		Memory::SafeCopyShallow(this->mItems+index,mSize-index,this->mItems+index+1,this->mCount-index-1);
		--this->mCount;

	}

	virtual void RemoveRange(size_t begin,size_t end)
	{
		MEDUSA_ASSERT_IF(end>begin&&end<this->mCount,"");
		Memory::DestoryRange(this->mItems+begin,end-begin);
		Memory::SafeCopyShallow(this->mItems+begin,mSize-begin,this->mItems+end+1,this->mCount-end-1);
		this->mCount-=end-begin;
	}

	virtual void RemoveAll(size_t srcBegin,size_t srcEnd,TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<this->mCount,"");

		while(true)
		{
			intp index=IndexOf(srcBegin,srcEnd,val);
			if (index>=0)
			{
				RemoveAt(index);
			}
			else
			{
				break;
			}
		}
	}

	virtual void Add(TParameterType val)
	{
		size_t newSize=Math::GetNewSizeSquare(mSize,this->mCount+1);
		Resize(newSize);

		size_t i=0;
		if (this->mCount>0)
		{
			i=Algorithm::BinarySearchLastGreaterThan<T,TSorter>(this->mItems,val,0,this->mCount-1);
			if (i==-1)	//not found
			{
				i=this->mCount;	//insert at last
			}
			else
			{
				//insert at i
				Memory::SafeCopyShallow(this->mItems+i+1,(mSize-i-1),this->mItems+i,(this->mCount-i));
			}
		}
		Memory::CopyConstruct(this->mItems+i,val);
		++this->mCount;

	}
	virtual bool Remove(TParameterType val)
	{
		intp index= IndexOf(0,this->mCount,val);
		if (index>=0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		Memory::DestoryRange(this->mItems,this->mCount);
		this->mCount=0;
	}

	virtual void Sort()
	{
		if (!this->IsEmpty())
		{
			Algorithm::QuickSort<T,TSorter>(*this);
		}
	}
#pragma endregion ISortedList interface


public:
	virtual void ReserveSize(size_t size)
	{
		Resize(size);
	}

	virtual void ReleaseExtraSize()
	{
		RETURN_IF_ZERO(mSize);

		if (this->mCount==0)
		{
			SAFE_FREE(this->mItems);
			mSize=0;
		}
		else
		{
			RETURN_IF_EQUAL(mSize,this->mCount);
			mSize=this->mCount;
			Memory::Realloc(this->mItems,mSize);
		}
	}

private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize>=size);

		mSize=size;
		Memory::Realloc(this->mItems,size);

		return true;
	}

protected:
	size_t mSize;

};

template<typename T,typename TCompare,typename TSorter >
WEAK_MULTIPLE_DEFINE const SortedList<T,TCompare,TSorter> SortedList<T,TCompare,TSorter>::Empty;

MEDUSA_END;