#pragma once

#include "Core/Collection/ICollection.h"
#include "Core/Collection/IList.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Algorithm/Algorithm.h"

MEDUSA_BEGIN;

class Linq
{
private:
	Linq();
	~Linq();
private:
	template<typename T,typename TCompare>
	static int STLCompare(const void* p,const void* q)
	{
		return TCompare::Compare(*(T*)p,*(T*)q);
	}
public:
	template<typename T>
	struct InnerTypes
	{
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
		typedef typename Compile::TypeTraits<T>::ConstReferenceType TConstReferenceType;

		typedef typename Compile::TypeTraits<T>::PointerType TPointerType;
		typedef typename Compile::TypeTraits<T>::ConstPointerType TConstPointerType;


		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

		typedef const Pattern::Delegate<void(TReferenceType item)>& CustomIteratorType;
		typedef const Pattern::Delegate<void(TConstReferenceType item)>& CustomConstIteratorType;
	};

public:
	template<typename TKey,typename TValue,typename TKeyValuePair,typename TKeyCompare,typename TValueCompare >
	static bool IsEqual(const IDictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>& first,const IDictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>& second)
	{
		RETURN_TRUE_IF(first.IsEmpty()&&second.IsEmpty());
		RETURN_FALSE_IF_NOT_EQUAL(first.GetCount(),second.GetCount());
		FOR_EACH_COLLECTION_VIRTUAL(i,first)
		{
			const TKey& firstKey=(*i).Key;
			const TValue& firstValue=(*i).Value;
			typename IDictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>::TValueConstPointerType secondValuePtr=second.TryGetValue(firstKey);
			RETURN_FALSE_IF(secondValuePtr==NULL||TValueCompare::Compare(firstValue,*secondValuePtr)!=0);
		}
		return true;
	}

	template<typename TKey,typename TValue,typename TKeyValuePair,typename TKeyCompare,typename TValueCompare >
	static bool IsEqual(const Dictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>& first,const Dictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>& second)
	{
		RETURN_TRUE_IF(first.IsEmpty()&&second.IsEmpty());
		RETURN_FALSE_IF_NOT_EQUAL(first.GetCount(),second.GetCount());
		FOR_EACH_COLLECTION(i,first)
		{
			const TKey& firstKey=(*i).Key;
			const TValue& firstValue=(*i).Value;
			typename Dictionary<TKey,TValue,TKeyValuePair,TKeyCompare,TValueCompare>::TValueConstPointerType secondValuePtr=second.TryGetValue(firstKey);
			RETURN_FALSE_IF(secondValuePtr==NULL||TValueCompare::Compare(firstValue,*secondValuePtr)!=0);
		}
		return true;
	}

	template<typename T>
	static bool IsEqual(const IList<T>& first,const IList<T>& second)
	{
		RETURN_TRUE_IF(first.IsEmpty()&&second.IsEmpty());
		RETURN_FALSE_IF_NOT_EQUAL(first.GetCount(),second.GetCount());
		size_t count=first.GetCount();
		FOR_EACH_SIZE(i,count)
		{
			RETURN_FALSE_IF_FALSE(second.Contains(first[i]));
		}
		return true;
	}

	template<typename T>
	static void DeleteIndexes(IList<T>& items,const IList<size_t>& indexes)
	{
		size_t count=indexes.GetCount();
		RETURN_IF_ZERO(count);
		FOR_EACH_SIZE(i,count)
		{
			typename IList<T>::TReferenceType item=items[indexes[i]];
			Memory::Delete(item);
		}
		items.RemoveIndexes(indexes);
	}

	template<typename T>
	static void DeleteItems(IList<T>& srcItems,const IList<T>& deadItems)
	{
		size_t deadCount=deadItems.GetCount();
		RETURN_IF_ZERO(deadCount);

		List<size_t> deadIndices;
		FOR_EACH_SIZE(i,deadCount)
		{
			int j=srcItems.IndexOf(deadItems[i]);
			if(j>=0)
			{
				deadIndices.Add((size_t)j);
				typename IList<T>::TReferenceType item=srcItems[j];
				Memory::Delete(item);
			}
		}

		srcItems.RemoveIndexes(deadIndices);
	}

	template<typename T>
	static T FirstOrDefault(const IList<T>& items)
	{
		if (items.IsEmpty())
		{
			return T();
		}
		return items.First();
	}

	template<typename T>
	static void ForEach(const ICollection<T>& items,typename InnerTypes<T>::CustomIteratorType iterator)
	{
		ForEach(items,0,items.GetCount(),iterator);
	}

	template<typename T>
	static void ForEach(const ICollection<T>& items,size_t srcBegin,size_t srcEnd,typename InnerTypes<T>::CustomIteratorType iterator)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=items.GetCount(),"");

		FOR_EACH_COLLECTION_BEGIN_END(i,srcBegin,srcEnd)
		{
			iterator(items[i]);
		}
	}

	template<typename T>
	static void ForEachConst(const ICollection<T>& items,typename InnerTypes<T>::CustomConstIteratorType iterator)
	{
		ForEachConst(items,0,items.GetCount(),iterator);
	}

	template<typename T>
	static void ForEachConst(const ICollection<T>& items,size_t srcBegin,size_t srcEnd,typename InnerTypes<T>::CustomConstIteratorType iterator)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=items.GetCount(),"");

		FOR_EACH_COLLECTION_BEGIN_END(i,srcBegin,srcEnd)
		{
			iterator(items[i]);
		}
	}


	template<typename T,typename TCompare>
	static void QuickSort(List<T,TCompare>& items)
	{
		if (items.GetCount()<=1)
		{
			return;
		}
		std::qsort(items.GetItems(),items.GetCount(),sizeof(T),Algorithm::STLCompare<T,TCompare>);
		//QuickSortHelper<TCompare>(items.GetItems(),0,items.GetCount()-1);
	}

	template<typename T,typename TCompare>
	static void InsertSort(List<T,TCompare>& items)
	{
		if (items.GetCount()<=1)
		{
			return;
		}
		Algorithm::InsertSortHelper<T,TCompare>(items.GetItems(),0,items.GetCount()-1);
	}

	template<typename T,typename TCompare>
	static intp BinarySearch(List<T,TCompare>& items,typename InnerTypes<T>::TParameterType key)
	{
		if (items.GetCount()==0)
		{
			return -1;
		}
		return std::bsearch(&key,items.GetItems(),items.GetCount(),sizeof(T),Algorithm::STLCompare<T,TCompare>);
		//return BinarySearchFirst<TCompare>(items.GetItems(),key,0,items.GetCount()-1);
	}
};

MEDUSA_END;