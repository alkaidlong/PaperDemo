#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename T>
	class LazyValue
	{
	public:
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
		typedef Delegate<void(TReferenceType)> TUpdateDelegateType;
	public:
		LazyValue():mIsDirty(true),mVersion(0) {}
		LazyValue(TParameterType val):mValue(val),mIsDirty(false),mVersion(0) {}
		LazyValue(const LazyValue& field){mValue=field.mValue;mIsDirty=field.IsDirty();mVersion=field.Version();}
		LazyValue& operator=(const LazyValue& field){mValue=field.mValue;mIsDirty=field.IsDirty();mVersion=field.Version();return *this;}
		LazyValue& operator=(TParameterType val){mValue=val;mIsDirty=false;++mVersion;return *this;}

	public:
		bool IsDirty() const { return mIsDirty; }
		void SetDirty() { mIsDirty = true;}
		size_t Version() const { return mVersion; }

		const T& Value()const
		{
			if (mIsDirty)
			{
				ForceUpdate();
			}

			return mValue;
		}

		T& Value()
		{
			if (mIsDirty)
			{
				ForceUpdate();
			}
			
			return mValue;
		}

		const T& OldValue()const{return mValue;}
		T& OldValue(){return mValue;}

		bool TryUpdate()const
		{
			if (mIsDirty)
			{
				ForceUpdate();
				return true;
			}
			return false;
		}

		void ForceUpdate()const
		{
			if (mUpdateDelegate.IsValid())
			{
				mUpdateDelegate(mValue);
			}
			mIsDirty=false;
			++mVersion;
		}
		void SetValue(TParameterType val) { mValue = val; mIsDirty=false;++mVersion;}
		void SetUpdateDelegate(TUpdateDelegateType val) { mUpdateDelegate = val; }

	private:
		mutable T mValue;
		mutable bool mIsDirty;
		mutable size_t mVersion;
		TUpdateDelegateType mUpdateDelegate;
	};
}
MEDUSA_END;