#pragma once
#include "Core/Collection/IList.h"
#include "Core/Memory/Memory.h"
#include "Core/Collection/STLPort.h"
#include "Core/Algorithm/Algorithm.h"
#include "Core/Math/MathHeader.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


template<typename T,class TCompare=DefaultCompare<T> >
class List:public IList<T>
{
	typedef List<T,TCompare> SelfType;

public:
	using IList<T>::IndexOf;
	using IList<T>::LastIndexOf;
	using IList<T>::First;
	using IList<T>::Last;
	using IList<T>::Reverse;
	using IList<T>::Contains;
	using IList<T>::Push;
	using IList<T>::PushRange;
	using IList<T>::AddRange;
	using IList<T>::Append;
	using IList<T>::AppendRange;
	using IList<T>::RemoveFirst;
	using IList<T>::RemoveLast;
	using IList<T>::RemoveAll;
	using IList<T>::IsEmpty;
	using IList<T>::operator [];


	typedef IList<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

	const static SelfType Empty;
public:
	using IEnumerable<T>::GetEnumeratorVirtual;
public:
	explicit List(size_t size=0)
	{
		this->mCount=0;
		mSize=size;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;
	}

	template<typename T1>
	List(const IEnumerable<T1>& items)
	{
		this->mCount=0;
		mSize=0;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;

		FOR_EACH_COLLECTION_VIRTUAL(i,items)
		{
			Append(*i);
		}
	}

	template<typename TInterator>
	List(TInterator begin,TInterator end)
	{
		this->mCount=0;
		mSize=0;
		this->mItems=NULL;

		FOR_EACH_COLLECTION_BEGIN_END(i,begin,end)
		{
			Append(*i);
		}
	}

	List(const List& items)
	{
		mSize=items.GetCount();
		this->mCount=mSize;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;

		Memory::CopyConstructIterator(this->mItems,items.GetItems(),mSize);
	}

	template<typename T1>
	List(const ICollection<T1>& items)
	{
		mSize=items.GetCount();
		this->mCount=mSize;
		this->mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;

		if (items.IsLinear())
		{
			Memory::CopyConstructIterator(this->mItems,items.GetItems(),mSize);
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i,items)
			{
				Append(*i);
			}
		}
	}

	List& operator=(const List<T,TCompare>& items)
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
	List& operator=(const List<T1,TCompare1>& items)
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

	virtual ~List(void)
	{
		Memory::DestoryRange(this->mItems,this->mCount);
		SAFE_FREE(this->mItems);
	}



public:
	size_t GetSize()const{return mSize;}
	bool IsFull()const{return this->mCount==mSize;}

#pragma region IEnumerable interface
public:
	class ListEnumerator:public IEnumerator<TReturnType>
	{
		friend class List<T,TCompare>;
		explicit ListEnumerator(T* items,size_t count):mItems(items),mCount(count),mIndex(-1){}

	public:
		virtual TReturnType Current(){return this->mItems[mIndex];}
		TReturnType operator*(){return this->mItems[mIndex];}

		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(intp)this->mCount;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		T* mItems;
		size_t mCount;
		intp mIndex;
	};

	class ConstListEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class List<T,TCompare>;
		explicit ConstListEnumerator(const T* items,size_t count):mItems(items),mCount(count),mIndex(-1){}

	public:
		virtual TConstReturnType Current(){return this->mItems[mIndex];}
		TConstReturnType operator*(){return this->mItems[mIndex];}

		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex<(intp)this->mCount;
		}
		virtual void Reset(){mIndex=-1;}
	protected:
		const T* mItems;
		size_t mCount;
		intp mIndex;
	};
public:
	ConstListEnumerator GetEnumerator()const{return ConstListEnumerator(this->mItems,this->mCount);}
	ListEnumerator GetEnumerator(){return ListEnumerator(this->mItems,this->mCount);}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstListEnumerator(this->mItems,this->mCount);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new ListEnumerator(this->mItems,this->mCount);}


#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	virtual bool IsLinear() const{return true;}
	virtual TConstPointerType GetItems() const { return this->mItems; }
	virtual TPointerType GetItems(){return this->mItems;}

	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(this->mItems);
		size_t count=Math::Min(this->mCount,(size_t)arraySize);
		Memory::CopyConstructIterator(outArray,this->mItems,count);
		return count;
	}



	virtual bool Contains(TParameterType val)const{RETURN_FALSE_IF_ZERO(this->mCount);return IndexOf(0,this->mCount-1,val)>=0;}

#pragma endregion ICollection interface

#pragma region IList interface

	virtual void SetRange(size_t index,const ICollection<T>& items)
	{
		MEDUSA_ASSERT_IF(index<=this->mCount,"");

		if (items.IsLinear())
		{
			SetRange(index,items.GetItems(),items.GetCount());
		}
		else
		{
			size_t count=items.GetCount();
			size_t newCount=index+count;
			if (newCount>this->mCount)
			{
				size_t j=this->mCount;
				FOR_EACH_COLLECTION_VIRTUAL(i,items)
				{
					if (j==0)
					{
						Append(*i);
						break;
					}
					else
					{
						--j;
						this->Set(index,*i);
						++index;
					}
				}
			}
			else
			{
				FOR_EACH_COLLECTION_VIRTUAL(i,items)
				{
					this->Set(index,*i);
					++index;
				}
			}
		}
	}

	virtual void SetRange(size_t index,const IList<T>& items)
	{
		SetRange(index,items.GetItems(),items.GetCount());
	}

	virtual void SetRange(size_t index,const T* items,size_t count)
	{
		MEDUSA_ASSERT_IF(index<=this->mCount,"");
		size_t newCount=index+count;

		if (newCount>this->mCount)
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,newCount);
			Resize(newSize);
			if (newCount>this->mCount)
			{
				this->mCount=newCount;
			}
		}

		Memory::CopyConstructIterator(this->mItems+index,items,count);
	}

	virtual void SetAll(TParameterType val)
	{
		Memory::Set(this->mItems,val,this->mCount);
	}


	virtual intp IndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<=this->mCount,"");
		FOR_EACH_UINT_BEGIN_END(i,srcBegin,srcEnd)
		{
			if (TCompare::Compare(this->mItems[i],val)==0)
			{
				return (intp)i;
			}
		}

		return -1;
	}


	virtual intp LastIndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<=this->mCount,"");

		FOR_EACH_INT_END_BEGIN(i,(intp)srcEnd-1,(intp)srcBegin-1)
		{
			if (TCompare::Compare(this->mItems[i],val)==0)
			{
				return (intp)i;
			}
		}


		return -1;
	}

	virtual void Reverse(size_t srcBegin,size_t srcEnd)
	{
		MEDUSA_ASSERT_IF(srcEnd>=srcBegin&&srcEnd<=this->mCount,"");

		while(srcBegin<srcEnd)
		{
			Math::Swap(this->mItems[srcBegin],this->mItems[srcEnd]);
			++srcBegin;
			--srcEnd;
		}
	}

	virtual void Insert(size_t index,TParameterType val,size_t count=1)
	{
		RETURN_IF_ZERO(count);
		MEDUSA_ASSERT_IF(index<this->mCount+count,"");
		if (this->mCount+count>mSize)
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,this->mCount+count);
			Resize(newSize);
		}


		if (this->mCount>0&&index!=this->mCount)
		{
			Memory::SafeCopyShallow(this->mItems+index+count,mSize-index-count,this->mItems+index,this->mCount-index);
		}

		if (count==1)
		{
			Memory::CopyConstruct(this->mItems+index,val);
		}
		else
		{
			Memory::CopyConstructRange(this->mItems+index,val,count);
		}
		this->mCount+=count;
	}

	virtual void InsertRange(size_t index,const T* items,size_t count)
	{
		RETURN_IF_ZERO(count);
		MEDUSA_ASSERT_IF(index<this->mCount+count,"");

		size_t newSize=Math::GetNewSizeSquare(mSize,this->mCount+count);
		Resize(newSize);

		if (this->mCount>0&&index!=this->mCount)
		{
			Memory::SafeCopyShallow(this->mItems+index+count,mSize-index-count,this->mItems+index,this->mCount-index);
		}

		Memory::CopyConstructIterator(this->mItems+index,items,count);
		this->mCount+=count;
	}

	virtual void InsertRange(size_t index,const IList<T>& items)
	{
		InsertRange(index,items.GetItems(),items.GetCount());
	}

	virtual void InsertRange(size_t index,const ICollection<T>& items)
	{
		MEDUSA_ASSERT_IF(index<=this->mCount,"");
		if (items.IsLinear())
		{
			InsertRange(index,items.GetItems(),items.GetCount());
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i,items)
			{
				Insert(index,*i);
				++index;
			}
		}

	}

	virtual void InsertRange(size_t index,const IEnumerable<T>& items)
	{
		MEDUSA_ASSERT_IF(index<=this->mCount,"");
		FOR_EACH_COLLECTION_VIRTUAL(i,items)
		{
			Insert(index,*i);
			++index;
		}

	}

	virtual void RemoveAt(size_t index)
	{
		MEDUSA_ASSERT_IF(index<this->mCount,"");
		Memory::Destory(this->mItems+index);
		Memory::SafeCopyShallow(this->mItems+index,mSize-index,this->mItems+index+1,this->mCount-index-1);
		--this->mCount;
	}


	virtual void RemoveRange(size_t index,size_t count)
	{
		MEDUSA_ASSERT_IF(index+count<=this->mCount,"");
		Memory::DestoryRange(this->mItems+index,count);
		Memory::SafeCopyShallow(this->mItems+index,mSize-index,this->mItems+index+count,this->mCount-index-count);
		this->mCount-=count;
	}

	virtual void RemoveIndexes(const IList<size_t>& indexes)
	{
		RETURN_IF_EMPTY(indexes);
		RETURN_IF_ZERO(this->mCount);

		size_t emptyIndex=indexes[0];
		size_t indexSize=indexes.GetCount();
		FOR_EACH_SIZE(i,indexSize)
		{
			size_t index=indexes[i];
			Memory::Destory(this->mItems+index);
			if (i<indexSize-1)
			{
				size_t nextIndex=indexes[i+1];
				size_t copyCount=nextIndex-index-1;
				if (copyCount>0)
				{
					Memory::SafeCopyShallow(this->mItems+emptyIndex,mSize-emptyIndex,this->mItems+index+1,copyCount);
					emptyIndex+=copyCount;
				}
			}
			else
			{
				size_t copyCount=this->mCount-index-1;
				if (copyCount>0)
				{
					Memory::SafeCopyShallow(this->mItems+emptyIndex,mSize-emptyIndex,this->mItems+index+1,copyCount);
				}
			}
		}

		this->mCount-=indexes.GetCount();
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
				srcBegin=index;
				--srcEnd;
			}
			else
			{
				break;
			}
		}
	}

	virtual void Add(TParameterType val,size_t count=1)
	{
		Append(val,count);
	}

	virtual bool Remove(TParameterType val)
	{
		RETURN_FALSE_IF_ZERO(this->mCount);
		intp index= IndexOf(0,this->mCount-1,val);
		if (index>=0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		RETURN_IF_ZERO(this->mCount);
		Memory::DestoryRange(this->mItems,this->mCount);
		this->mCount=0;
	}

	virtual void Sort()
	{
		if (!IsEmpty())
		{
			Algorithm::QuickSortHelper<T,TCompare>(this->mItems,0,this->mCount-1);
		}
	}


#pragma endregion IList interface
public:
	TReferenceType NewAdd()
	{
		if (IsFull())
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,mSize+1);
			Resize(newSize);
		}

		Memory::Construct(this->mItems+this->mCount);
		return this->mItems[this->mCount++];
	}

	template<typename TInterator>
	void AddRange(TInterator begin,TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i,begin,end)
		{
			Add(*i);
		}
	}

	void PushRange(const IList<T>& items){ InsertRange(0,items);}

	template<typename TInterator>
	void PushRange(TInterator begin,TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i,begin,end)
		{
			Push(*i);
		}
	}

	void AppendRange(const IList<T>& items){ InsertRange(this->mCount,items);}

	template<typename TInterator>
	void AppendRange(TInterator begin,TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i,begin,end)
		{
			Append(*i);
		}
	}


	template<size_t size>
	void AppendRange(const T (&items)[size])
	{
		AppendRange(items,size);
	}

	void AppendRange(const T* items,size_t count)
	{
		size_t newSize=Math::GetNewSizeSquare(mSize,this->mCount+count);
		Resize(newSize);

		Memory::CopyConstructIterator(this->mItems+this->mCount,items,count);
		this->mCount+=count;
	}

	void Merge(const List<T>& items)
	{
		FOR_EACH_COLLECTION(i,items)
		{
			if (!Contains(*i))
			{
				Add(*i);
			}
		}
	}

	void Merge(const IList<T>& items)
	{
		FOR_EACH_COLLECTION_VIRTUAL(i,items)
		{
			if (!Contains(*i))
			{
				Add(*i);
			}
		}
	}



	void ForceSetCount(size_t newCount)
	{
		MEDUSA_ASSERT_IF(newCount<=mSize,"");
		this->mCount=newCount;
	}

	void ForceConstructAll()
	{
		Memory::ConstructRange(this->mItems,this->mCount);
	}

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

	MemoryData<T> ToData()const{return MemoryData<T>::FromStatic(this->mItems,this->mCount);}
private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize>=size);
		Memory::Realloc(this->mItems,size);
		mSize=size;
		return true;
	}

protected:
	size_t mSize;

};

template<typename T,class TCompare>
WEAK_MULTIPLE_DEFINE const List<T,TCompare> List<T,TCompare>::Empty;

MEDUSA_END;