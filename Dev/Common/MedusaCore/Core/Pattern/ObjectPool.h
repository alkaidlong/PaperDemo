#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template <typename TObject,typename TObjectCompare=DefaultCompare<TObject>,typename TObjectNewer=DefaultNewer<TObject>>
	class ObjectPool
	{
	public:
		typedef typename Compile::TypeTraits<TObject>::ReferenceType TObjectReferenceType;
		typedef typename Compile::TypeTraits<TObject>::ConstReferenceType TObjectConstReferenceType;

		typedef typename Compile::TypeTraits<TObject>::PointerType TObjectPointerType;
		typedef typename Compile::TypeTraits<TObject>::ConstPointerType TObjectConstPointerType;

		typedef typename Compile::TypeTraits<TObject>::ParameterType TObjectParameterType;

		typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

		typedef List<TObject,TObjectCompare> ItemCollection;
	public:
		ObjectPool(){}
		virtual ~ObjectPool(){Clear();}
	public:
		bool IsEmpty()const{return GetCount()==0;} 
		size_t GetCount() const{return mItems.GetCount();}
	public:
		void Clear()
		{
			SAFE_DELETE_COLLECTION(mItems);
		}

		TObject Create()
		{
			if (!mItems.IsEmpty())
			{
				TObject obj=mItems.Last();
				mItems.RemoveLast();
				return obj;
			}
			return TObjectNewer::New();
		}

		void Recycle(TObjectParameterType obj)
		{
			mItems.Append(obj);
		}

	protected:
		ItemCollection mItems;
	};
}
MEDUSA_END;