#pragma once

#include "Core/Collection/ICollection.h"



MEDUSA_BEGIN;

template<typename T>
struct LinkedListNode
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	LinkedListNode(TParameterType val)
	{
		Prev=NULL;
		Next=NULL;
		Value=val;
	}

	LinkedListNode()
	{
		Prev=NULL;
		Next=NULL;
	}

	LinkedListNode* Prev;
	LinkedListNode* Next;
	T Value;
};

template<typename T >
class ILinkedList:public ICollection<T>
{
	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;
    
public:
	typedef LinkedListNode<T>* NodePtr;

	NodePtr AddAfter(NodePtr node, TParameterType value)
	{
		NodePtr newNode=new LinkedListNode<T>(value);
		AddAfter(node,newNode);
		return newNode;
	}

	NodePtr AddBefore(NodePtr node, TParameterType value)
	{
		NodePtr newNode=new LinkedListNode<T>(value);
		AddBefore(node,newNode);
		return newNode;
	}
	NodePtr AddFirst(TParameterType value)
	{
		NodePtr newNode=new LinkedListNode<T>(value);
		AddFirst(newNode);
		return newNode;
	}
	NodePtr AddLast(TParameterType value)
	{
		NodePtr newNode=new LinkedListNode<T>(value);
		AddLast(newNode);
		return newNode;
	}

	bool RemoveFirst(TParameterType val)
	{
		NodePtr node=FindFirst(val);
		if (node!=NULL)
		{
			Remove(node);
			return true;
		}
		return false;
	}

	virtual bool RemoveLast(TParameterType val)
	{
		NodePtr node=FindLast(val);
		if (node!=NULL)
		{
			Remove(node);
			return true;
		}
		return false;
	}

	void RemoveFirst()
	{
		NodePtr node=FirstNode();
		if (node!=NULL)
		{
			Remove(node);
		}
	}
	void RemoveLast()
	{
		NodePtr node=LastNode();
		if (node!=NULL)
		{
			Remove(node);
		}
	}

	TConstReturnType First()const
	{
		NodePtr node=FirstNode();
		MEDUSA_ASSERT_NOT_NULL(node,"");
		return node->Value;	
	}
	TConstReturnType Last()const
	{
		NodePtr node=LastNode();
		MEDUSA_ASSERT_NOT_NULL(node,"");
		return node->Value;		
	}

	TReferenceType First()
	{
		NodePtr node=FirstNode();
		MEDUSA_ASSERT_NOT_NULL(node,"");
		return node->Value;		
	}
	TReferenceType Last()
	{
		NodePtr node=LastNode();
		MEDUSA_ASSERT_NOT_NULL(node,"");
		return node->Value;		
	}

public:
	virtual void AddAfter(NodePtr node, NodePtr newNode)=0;
	virtual void AddBefore(NodePtr node, NodePtr newNode)=0;
	virtual void AddFirst(NodePtr node)=0;
	virtual void AddLast(NodePtr node)=0;
	virtual NodePtr FindFirst(TParameterType value)const=0;
	virtual NodePtr FindLast(TParameterType value)const=0;
	virtual NodePtr Remove(NodePtr node)=0;
	virtual NodePtr Delete(NodePtr node)=0;


	virtual NodePtr FirstNode()const=0;
	virtual NodePtr LastNode()const=0;

	virtual bool Contains(NodePtr node)const=0;

	virtual void RemoveAll(TParameterType val)=0;

	virtual void Add(TParameterType val)=0;
	virtual bool Remove(TParameterType val)=0;
	virtual void Clear()=0;
};

MEDUSA_END;