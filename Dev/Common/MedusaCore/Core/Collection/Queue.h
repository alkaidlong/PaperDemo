#pragma once
#include "Core/Collection/ICollection.h"
#include "Core/Collection/STLPort.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/MathHeader.h"

MEDUSA_BEGIN;



template<typename T,class TCompare=DefaultCompare<T> >
class Queue:public ICollection<T>
{
	typedef Queue<T,TCompare> SelfType;
    
public:
	using IEnumerable<T>::GetEnumeratorVirtual;
	using  ICollection<T>::IsEmpty;
	using  ICollection<T>::GetByteSize;
    
	typedef ICollection<T> BaseType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TParameterType TParameterType;
    
	const static SelfType Empty;
public:
	explicit Queue(size_t size=0)
	{
		this->mCount=0;
		mSize=size;
		mHead=-1;
		mTail=-1;
		mItems=mSize!=0?(T*)malloc(sizeof(T)*mSize):NULL;
	}

	virtual ~Queue(void)
	{
		Memory::DestoryRange(mItems,this->mCount);
		SAFE_FREE(mItems);
	}


public:
	size_t GetSize()const{return mSize;}
	bool IsFull()const{return this->mCount==mSize;}

#pragma region IEnumerable interface
public:
	class QueueEnumerator:public IEnumerator<TReturnType>
	{
		friend class Queue<T,TCompare>;
		explicit QueueEnumerator(T* items,size_t size,size_t head,size_t tail,size_t count):mItems(items),mSize(size),mHead(head),mTail(tail),mIndex(head-1),mCount(count),mEnumCount(count){}

	public:
		virtual TReturnType Current(){return mItems[mIndex];}
		TReturnType operator*(){return mItems[mIndex];}

		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_ZERO(this->mCount);
			RETURN_FALSE_IF_ZERO(mEnumCount);

			mIndex=(mIndex+1)%mSize;
			--mEnumCount;

			if (mHead<=mTail)
			{
				return mIndex>=mHead&&mIndex<=mTail;
			}
			else
			{
				return (mIndex>=mHead&&mIndex<(intp)mSize)||(mIndex>=0&&mIndex<=mTail);
			}
		}
		virtual void Reset(){mIndex=mHead-1;mEnumCount=this->mCount;}
	protected:
		T* mItems;
		intp mHead;
		intp mTail;

		size_t mSize;
		intp mIndex;
		size_t mCount;
		size_t mEnumCount;

	};

	class ConstQueueEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class Queue<T,TCompare>;
		explicit ConstQueueEnumerator(const T* items,size_t size,intp head,intp tail,size_t count):mItems(items),mSize(size),mHead(head),mTail(tail),mIndex(head-1),mCount(count),mEnumCount(count){}

	public:
		virtual TConstReturnType Current(){return mItems[mIndex];}
		TConstReturnType operator*(){return mItems[mIndex];}

		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_ZERO(this->mCount);
			RETURN_FALSE_IF_ZERO(mEnumCount);

			mIndex=(mIndex+1)%mSize;
			--mEnumCount;

			if (mHead<=mTail)
			{
				return mIndex>=mHead&&mIndex<=mTail;
			}
			else
			{
				return (mIndex>=mHead&&mIndex<(intp)mSize)||(mIndex>=0&&mIndex<=mTail);
			}
		}
		virtual void Reset(){mIndex=mHead-1;mEnumCount=this->mCount;}
	protected:
		const T* mItems;
		intp mHead;
		intp mTail;

		size_t mSize;
		intp mIndex;
		size_t mCount;
		size_t mEnumCount;
	};
	public:
		ConstQueueEnumerator GetEnumerator()const{return ConstQueueEnumerator(mItems,mSize,mHead,mTail,this->mCount);}
		QueueEnumerator GetEnumerator(){return QueueEnumerator(mItems,mSize,mHead,mTail,this->mCount);}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstQueueEnumerator(mItems,mSize,mHead,mTail,this->mCount);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new QueueEnumerator(mItems,mSize,mHead,mTail,this->mCount);}


#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	virtual size_t GetCount() const{return this->mCount;}
	virtual bool IsLinear() const{return true;}
	virtual TConstPointerType GetItems() const { return mItems; }
	virtual TPointerType GetItems() { return mItems; }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT_NOT_NULL(outArray,"null parameter");
		MEDUSA_ASSERT_NOT_ZERO(arraySize,"arraySize==0");
		RETURN_ZERO_IF_ZERO(this->mCount);


		if (mHead<=mTail)
		{
			size_t count=Math::Min(this->mCount,arraySize);
			Memory::SafeCopy(outArray,arraySize,mItems+mHead,this->mCount);
			return count;
		}
		else
		{
			size_t tailSize=mTail+1;
			size_t count=Math::Min(tailSize,arraySize);
			Memory::SafeCopy(outArray,arraySize,mItems,count);
			RETURN_OBJECT_IF_ZERO(count,tailSize);
			arraySize-=tailSize;
			count=Math::Min((size_t)(mSize-mHead),arraySize);
			Memory::SafeCopy(outArray+tailSize,arraySize,mItems+mHead,count);
			return tailSize+count;
		}
	}

	virtual bool Contains(TParameterType val)const
	{
		size_t index=mHead;
		size_t num2=this->mCount;
		while (num2-- > 0)
		{
			if (mItems[index]==val)
			{
				return true;
			}
			index = (index + 1) % mSize;
		}
		return false;
	}

#pragma endregion ICollection interface
	void Clear()
	{
		if (mHead<=mTail)
		{
			Memory::DestoryRange(mItems+mHead,mTail-mHead);
		}
		else
		{
			Memory::DestoryRange(mItems,mTail+1);
			Memory::DestoryRange(mItems+mHead,mSize-mHead);
		}
		
		this->mCount=0;
		mHead=-1;
		mTail=-1;
	}

	void Pop()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount,"Empty");
		Memory::Destory(mItems+mHead);
		mHead=(mHead+1)%mSize;
		this->mCount--;
	}

	void Push(TParameterType val)
	{
		if (IsFull())
		{
			size_t newSize=Math::GetNewSizeSquare(mSize,this->mCount+1);
			Resize(newSize);
		}

		if (this->mCount==0)
		{
			mHead=0;
			mTail=0;
		}
		else
		{
			mTail=(mTail+1)%mSize;
		}
		Memory::CopyConstruct(mItems+mTail,val);
		
		this->mCount++;
	}

	bool Remove(TParameterType val)
	{
		int index=IndexOf(val);
		if(index<0)
		{
			return false;
		}

		if (mHead<=mTail)
		{
			Memory::SafeCopyShallow(mItems+index,mTail-index+1,mItems+index+1,mTail-index);
			mTail=(mTail-1)%mSize;
			--this->mCount;
		}
		else
		{
			if (index>=mHead&&index<(intp)mSize)
			{
				Memory::SafeCopyShallow(mItems+index,mSize-index+1,mItems+index+1,mSize-index);
				Memory::SafeCopyShallow(mItems,mTail-index+1,mItems+1,mTail-index);
				mTail=(mTail-1)%mSize;
				--this->mCount;
			}
		}

		return true;

	}


	int IndexOf(TParameterType val)const
	{
		if (this->mCount==0)
		{
			return -1;
		}

		int index=mHead%mSize;
		int count=this->mCount;
		if (mHead<=mTail)
		{
			while(count>0&&index>=mHead&&index<=mTail)
			{
				if(mItems[index]==val)
				{
					return index;
				}
				index=(index+1)%mSize;
				--count;
			}
		}
		else
		{
			while(count>0&&((index>=mHead&&index<(intp)mSize)||(index>=0&&index<=mTail)))
			{
				if(mItems[index]==val)
				{
					return index;
				}
				index=(index+1)%mSize;
				--count;
			}
		}

		return -1;
	}

	TConstReturnType Head()const
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount,"Empty");
		return mItems[mHead];
	}

	TReturnType Head()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount,"Empty");
		return mItems[mHead];
	}

	TConstReturnType Tail()const
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount,"Empty");
		intp tailIndex=(mTail+mSize-1)%mSize;
		return mItems[tailIndex];
	}

	TReturnType Tail()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount,"Empty");
		intp tailIndex=(mTail+mSize-1)%mSize;
		return mItems[tailIndex];
	}
public:
	virtual void ReserveSize(size_t size)
	{
		Resize(size);
	}
private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize>=size);
		mSize=size;

		if (mHead <= mTail)
		{
			Memory::Realloc(mItems,size);
		}
		else
		{

			T* tempItems=(T*)malloc(mSize*sizeof(T));
			size_t lastCount=this->mCount-mHead;
			Memory::SafeCopyShallow(tempItems,mSize*sizeof(T),mItems+mHead,lastCount);
			Memory::SafeCopyShallow(tempItems+lastCount,(mSize-lastCount)*sizeof(T),mItems,mTail+1);
			SAFE_FREE(mItems);
			mItems=tempItems;
			mHead = 0;
			mTail = this->mCount-1;
		}

		return true;
	}

	

protected:
	T* mItems;
	size_t mSize;


	intp mHead;	//pointer to first element
	intp mTail;	//pointer to last element

};


template<typename T,class TCompare>
WEAK_MULTIPLE_DEFINE const Queue<T,TCompare> Queue<T,TCompare>::Empty;

MEDUSA_END;