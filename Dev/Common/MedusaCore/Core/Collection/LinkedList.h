#pragma once

#include "Core/Collection/ILinkedList.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;


template<typename T,typename TCompare=DefaultCompare<T> >
class LinkedList:public ILinkedList<T>
{
public:
	typedef LinkedList<T,TCompare> SelfType;
    typedef ILinkedList<T> BaseType;
    typedef typename BaseType::NodePtr NodePtr;
    typedef typename IEnumerable<T>::TConstPointerType TConstPointerType;
	typedef typename IEnumerable<T>::TPointerType TPointerType;
	typedef typename IEnumerable<T>::TParameterType TParameterType;
	typedef typename IEnumerable<T>::TReturnType TReturnType;
	typedef typename IEnumerable<T>::TConstReturnType TConstReturnType;
	typedef typename IEnumerable<T>::TReferenceType TReferenceType;

	const static SelfType Empty;
public:
	LinkedList()
	{
		mHead.Next=&mTail;
		mTail.Prev=&mHead;
	}

	template<typename T1>
	LinkedList(const IEnumerable<T1>& items)
	{
		this->mCount=0;
		mHead.Next=&mTail;
		mTail.Prev=&mHead;
		CopyFrom(items);
	}

	LinkedList(const LinkedList& items)
	{
		this->mCount=0;
		mHead.Next=&mTail;
		mTail.Prev=&mHead;
		CopyFrom(items);
	}

	LinkedList& operator=(const LinkedList<T>& items)
	{
		this->mCount=0;
		mHead.Next=&mTail;
		mTail.Prev=&mHead;
		CopyFrom(items);
		return *this;
	}

	template<typename T1>
	LinkedList& operator=(const LinkedList<T1>& items)
	{
		this->mCount=0;
		mHead.Next=&mTail;
		mTail.Prev=&mHead;
		CopyFrom(items.ConstBegin(),items.ConstEnd());
		return *this;
	}

	virtual ~LinkedList(void)
	{
		Clear();
	}


public:

	NodePtr operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index<this->mCount+1,"");
		NodePtr node=mHead.Next;
		while(index!=0)
		{
			--index;
			MEDUSA_ASSERT_NOT_NULL(node,"");
			node=node->Next;
		}
		return node;
	}

	const NodePtr operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index<this->mCount+1,"");
		NodePtr node=mHead.Next;
		while(index!=0)
		{
			--index;
			MEDUSA_ASSERT_NOT_NULL(node,"");
			node=node->Next;
		}
		return node;
	}

#pragma region IEnumerable interface
public:

	class LinkListEnumerator:public IEnumerator<TReturnType>
	{
		friend class LinkedList<T,TCompare>;
		explicit LinkListEnumerator(NodePtr head):mHead(head),mIndex(mHead){}

	public:
		virtual TReturnType Current(){return mIndex->Value;}
		TReturnType operator*(){return mIndex->Value;}


		virtual bool MoveNext()
		{
			mIndex=mIndex->Next;
			return mIndex!=NULL;
		}
		virtual void Reset(){mIndex=mHead;}
	protected:
		NodePtr mHead;
		NodePtr mIndex;
	};

	class ConstLinkListEnumerator:public IEnumerator<TConstReturnType>
	{
		friend class LinkedList<T,TCompare>;
		explicit ConstLinkListEnumerator( const LinkedListNode<T>* head):mHead(head),mIndex(mHead){}

	public:
		virtual TConstReturnType Current(){return mIndex->Value;}
		TConstReturnType operator*(){return mIndex->Value;}


		virtual bool MoveNext()
		{
			mIndex=mIndex->Next;
			return mIndex!=NULL;
		}
		virtual void Reset(){mIndex=mHead;}
	protected:
		const LinkedListNode<T>* mHead;
		const LinkedListNode<T>* mIndex;
	};
	public:
		ConstLinkListEnumerator GetEnumerator()const{return ConstLinkListEnumerator(&mHead);}
		LinkListEnumerator GetEnumerator(){return LinkListEnumerator(&mHead);}
protected:
	virtual IEnumerator<TConstReturnType>* GetEnumeratorVirtualHelper()const{return new ConstLinkListEnumerator(&mHead);}
	virtual IEnumerator<TReturnType>* GetEnumeratorVirtualHelper(){return new LinkListEnumerator(&mHead);}


#pragma endregion IEnumerable interface


#pragma region ICollection interface
		
public:
	virtual bool IsLinear() const{return false;}
	virtual TConstPointerType GetItems() const 
	{
		//MEDUSA_NOT_IMPLEMENT();
		return NULL; 
	}
	virtual TPointerType GetItems() 
	{
		//MEDUSA_NOT_IMPLEMENT();
		return NULL; 
	}
	virtual bool Contains(TParameterType val)const
	{
		NodePtr node=FindFirst(val);
		return node!=NULL;
	}


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		size_t index=0;
		for (NodePtr node=mHead.Next;node!=&mTail;node=node->Next)
		{
			Memory::CopyConstruct(outArray+index,node->Value);
			++index;
		}
		return index;
	}

	

#pragma endregion ICollection interface


#pragma region ILinkedList interface
public:
	virtual void AddAfter(NodePtr node, NodePtr newNode)
	{
		MEDUSA_ASSERT_NOT_NULL(node,"");
		MEDUSA_ASSERT_NOT_NULL(newNode,"");

		newNode->Prev=node;
		newNode->Next=node->Next;
		if (node->Next!=NULL)
		{
			node->Next->Prev=newNode;
		}
		node->Next=newNode;
		++this->mCount;
	}
	virtual void AddBefore(NodePtr node, NodePtr newNode)
	{
		MEDUSA_ASSERT_NOT_NULL(node,"");
		MEDUSA_ASSERT_NOT_NULL(newNode,"");
		newNode->Next=node;
		newNode->Prev=node->Prev;

		if (node->Prev!=NULL)
		{
			node->Prev->Next=newNode;
		}
		node->Prev=newNode;
		++this->mCount;
	}
	virtual void AddFirst(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node,"");

		AddAfter(&mHead,node);
	}
	virtual void AddLast(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node,"");

		AddBefore(&mTail,node);
	}

	virtual NodePtr FindFirst(TParameterType val)const
	{
		for (NodePtr node=mHead.Next;node!=&mTail;node=node->Next)
		{
			if ( TCompare::Compare(node->Value,val)==0)
			{
				return node;
			}
		}

		return NULL;

	}
	virtual NodePtr FindLast(TParameterType val)const
	{
		for (NodePtr node=mTail.Prev;node!=&mHead;node=node->Prev)
		{
			if ( TCompare::Compare(node->Value,val)==0)
			{
				return node;
			}
		}

		return NULL;
	}

	virtual NodePtr Remove(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node,"");
		if(node->Prev!=NULL)
		{
			node->Prev->Next=node->Next;
		}

		if (node->Next!=NULL)
		{
			node->Next->Prev=node->Prev;
		}
		--this->mCount;
		return node->Next;
	}


	virtual NodePtr Delete(NodePtr node)
	{
		NodePtr oldNode=node;
		node=Remove(node);
		SAFE_DELETE(oldNode);
		return node;
	}

	
	virtual NodePtr FirstNode()const
	{
		if (mHead.Next==&mTail)
		{
			return NULL;
		}
		return mHead.Next;
	}

	virtual NodePtr LastNode()const
	{
		if (mTail.Prev==&mHead)
		{
			return NULL;
		}
		return mTail.Prev;
	}

	virtual bool Contains(NodePtr node)const
	{
		for (NodePtr node1=mHead.Next;node1!=&mTail;node1=node1->Next)
		{
			if (node1==node)
			{
				return true;
			}
		}
		return false;
	}

	virtual void RemoveAll(TParameterType val)
	{
		for (NodePtr node=mHead.Next;node!=&mTail;)
		{
			if ( TCompare::Compare(node->Value,val)==0)
			{
				node->Prev->Next=node->Next;
				if (node->Next!=NULL)
				{
					node->Next->Prev=node->Prev;
				}
				node=node->Next;

				NodePtr tempNode=node;
				SAFE_DELETE(tempNode);
			}
			else
			{
				node=node->Next;
			}
		}
		this->mCount=0;
	}
	virtual void Add(TParameterType val)
	{
		NodePtr newNode=new LinkedListNode<T>(val);
		AddLast(newNode);
	}

	virtual bool Remove(TParameterType val)
	{
		NodePtr node= FindFirst(val);
		if (node!=NULL)
		{
			Remove(node);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		this->mCount=0;
		for (NodePtr node=mHead.Next;node!=&mTail;)
		{
			NodePtr tempNode=node;
			node=node->Next;
			SAFE_DELETE(tempNode);
		}

		mHead.Next=&mTail;
		mTail.Prev=&mHead;
	}

#pragma endregion ILinkedList interface

protected:
	LinkedListNode<T> mHead;
	LinkedListNode<T> mTail;
};


template<typename T,class TCompare>
WEAK_MULTIPLE_DEFINE const LinkedList<T,TCompare> LinkedList<T,TCompare>::Empty;

MEDUSA_END;