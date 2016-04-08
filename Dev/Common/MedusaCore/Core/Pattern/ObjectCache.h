#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template <typename TId,typename TObject,typename THashCoder=DefaultHashCoder<TId>,typename TKeyCompare=DefaultCompare<TId> >
	class ObjectCache
	{
	public:
		typedef typename Compile::TypeTraits<TObject>::ReferenceType TObjectReferenceType;
		typedef typename Compile::TypeTraits<TObject>::ConstReferenceType TObjectConstReferenceType;

		typedef typename Compile::TypeTraits<TObject>::PointerType TObjectPointerType;
		typedef typename Compile::TypeTraits<TObject>::ConstPointerType TObjectConstPointerType;

		typedef typename Compile::TypeTraits<TId>::ParameterType TIdParameterType;
		typedef typename Compile::TypeTraits<TObject>::ParameterType TObjectParameterType;

		typedef typename Compile::TypeTraits<TId>::ReferenceType TIdReferenceType;

		typedef typename Compile::TypeTraits<TId>::PointerType TIdPointerType;
		typedef typename Compile::TypeTraits<TId>::ConstPointerType TIdConstPointerType;
	public:
		ObjectCache(){}
		virtual ~ObjectCache(){Clear();}
	public:
		bool IsEmpty()const{return GetCount()==0;} 
		size_t GetCount() const{return mItems.GetCount();}
		const Dictionary<TId,TObject,THashCoder,TKeyCompare>& GetItems()const{return mItems;}
	public:
		void Clear()
		{
			SAFE_DELETE_DICTIONARY_VALUE(mItems);
		}

		bool ContainsId(TIdParameterType id)const
		{
			return mItems.ContainsKey(id);
		}

		bool ContainsObject(TObjectParameterType object)const
		{
			return mItems.ContainsValue(object);
		}

		TObjectReferenceType GetObject(TIdParameterType id)
		{
			return mItems.GetValue(id);
		}
		TObjectConstReferenceType GetObject(TIdParameterType id)const
		{
			return mItems.GetValue(id);
		}

		TObjectPointerType TryGetObject(TIdParameterType id)
		{
			return mItems.TryGetValue(id);
		}

		TObjectConstPointerType TryGetObject(TIdParameterType id)const
		{
			return mItems.TryGetValue(id);
		}

		TObject TryGetObjectWithFailed(TIdParameterType id,TObjectParameterType failedReturn)const
		{
			return mItems.TryGetValueWithFailed(id,failedReturn);
		}

		TObject TryGetObjectWithFailed(TIdParameterType id,TObjectParameterType failedReturn)
		{
			return mItems.TryGetValueWithFailed(id,failedReturn);
		}

		TIdPointerType TryGetId(TObjectParameterType object)
		{
			return mItems.TryGetKey(object);
		}

		TIdConstPointerType TryGetId(TObjectParameterType object)const
		{
			return mItems.TryGetKey(object);
		}

		void Add(TIdParameterType id,TObjectParameterType object)
		{
			mItems.Add(id,object);
		}

		bool RemoveId(TIdParameterType id)
		{
			return mItems.RemoveKey(id);
		}
		bool RemoveObject(TObjectParameterType object)
		{
			return mItems.RemoveValue(object);
		}

		bool DeleteId(TIdParameterType id)
		{
			TObjectPointerType outObject=mItems.TryGetValue(id);
			if (outObject!=NULL)
			{
				if (RemoveId(id))
				{
					SAFE_DELETE(*outObject);
					return true;
				}
			}

			return false;
		}

		bool DeleteObject(TObjectParameterType object)
		{
			TIdPointerType outId=mItems.TryGetKey(object); 
			if(outId!=NULL)
			{
				SAFE_DELETE(object);
				bool result=RemoveId(*outId);
				return result;
			}

			SAFE_DELETE(object);
			return false;
		}

	protected:
		Dictionary<TId,TObject,THashCoder,TKeyCompare> mItems;
	};
}
MEDUSA_END;