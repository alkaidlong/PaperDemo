#pragma once
#include "Core/Collection/ICollection.h"
#include "Core/Collection/List.h"

#include "Core/Collection/STLPort.h"

MEDUSA_BEGIN;


template<typename T,class TCompare=DefaultCompare<T> >
class Stack:public ICollection<T>
{
	typedef Stack<T,TCompare> SelfType;
	typedef List<T,TCompare> ContainerType;

public:
    
	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;
    
	using IEnumerable<T>::GetEnumeratorVirtual;
	using  ICollection<T>::IsEmpty;
	using  ICollection<T>::GetByteSize;
	const static SelfType Empty;
public:
	explicit Stack(size_t size=0):mItems(size)
	{
		
	}

	template<typename T1>
	Stack(const IEnumerable<T1>& items):mItems(items)
	{
		this->mCount=mItems.GetCount();
	}

	Stack(const Stack& items):mItems(items)
	{
		this->mCount=mItems.GetCount();
	}

	template<typename T1>
	Stack(const ICollection<T1>& items):mItems(items)
	{
		this->mCount=mItems.GetCount();
	}

	Stack& operator=(const Stack<T>& items)
	{
		mItems=items;
		this->mCount=mItems.GetCount();
		return *this;
	}

	template<typename T1>
	Stack& operator=(const Stack<T1>& items)
	{
		mItems=items;
		this->mCount=mItems.GetCount();
		return *this;
	}

	virtual ~Stack(void)
	{
		
	}
public:
	size_t GetSize()const{return mItems.GetSize();}
	bool IsFull()const{return mItems.IsFull();}

#pragma region IEnumerable interface
public:
	class StackEnumerator:public IEnumerator<TReturnType>
	{
		friend class Stack<T,TCompare>;
		explicit StackEnumerator(T* items,size_t count):mItems(items),mCount(count),mIndex(count){}

	public:
		virtual TReturnType Current(){return mItems[mIndex];}
		TReturnType operator*(){return mItems[mIndex];}

		virtual bool MoveNext()
		{
			--mIndex;
			return mIndex>=0;
		}
		virtual void Reset(){mIndex=this->mCount;}
	protected:
		T* mItems;
		size_t mCount;
		intp mIndex;
	};

	class ConstStackEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class Stack<T,TCompare>;
		explicit ConstStackEnumerator(const T* items,size_t count):mItems(items),mCount(count),mIndex(count){}

	public:
		virtual TConstReturnType Current(){return mItems[mIndex];}
		TConstReturnType operator*(){return mItems[mIndex];}

		virtual bool MoveNext()
		{
			--mIndex;
			return mIndex>=0;
		}
		virtual void Reset(){mIndex=this->mCount;}
	protected:
		const T* mItems;
		size_t mCount;
		intp mIndex;
	};
public:
	ConstStackEnumerator GetEnumerator()const{return ConstStackEnumerator(mItems.GetItems(),mItems.GetCount());}
	StackEnumerator GetEnumerator(){return StackEnumerator(mItems.GetItems(),mItems.GetCount());}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstStackEnumerator(mItems.GetItems(),mItems.GetCount());}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new StackEnumerator(mItems.GetItems(),mItems.GetCount());}


#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	
	virtual bool IsLinear() const{return mItems.IsLinear();}
	virtual TConstPointerType GetItems() const { return mItems.GetItems(); }
	virtual TPointerType GetItems() { return mItems.GetItems(); }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		return mItems.CopyTo(outArray,arraySize);
	}

	void Clear()
	{
		mItems.Clear();
		this->mCount=0;
	}

	virtual bool Contains(TParameterType val)const{return mItems.Contains(val);}

#pragma endregion ICollection interface

	void Push(TParameterType val)
	{
		mItems.Append(val);
		this->mCount=mItems.GetCount();
	}

	TReferenceType Pop()
	{
		MEDUSA_ASSERT_NOT_EMPTY(mItems,"Empty");
		TReferenceType last=mItems.Last();
		mItems.RemoveLast();
		this->mCount=mItems.GetCount();
		return last;
	}

	TConstReturnType Top()const
	{
		return mItems.Last();
	}

	TReferenceType Top()
	{
		return mItems.Last();
	}

	static Stack* New(TParameterType p1)
	{
		Stack* stack=new Stack();
		stack->Push(p1);
		return stack;
	}

protected:
	ContainerType mItems;
};

template<typename T,class TCompare>
WEAK_MULTIPLE_DEFINE const Stack<T,TCompare> Stack<T,TCompare>::Empty;

MEDUSA_END;