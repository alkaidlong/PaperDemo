#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename T>
	class NullableValue
	{
	public:
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
	public:
		NullableValue():mHasValue(false) {}
		NullableValue(TParameterType val):mValue(val),mHasValue(true) {}
		NullableValue(const NullableValue& field){mValue=field.mValue;mHasValue=field.HasValue();}
		NullableValue& operator=(const NullableValue& field){mValue=field.mValue;mHasValue=field.HasValue();return *this;}
		NullableValue& operator=(TParameterType val){mValue=val;mHasValue=true;return *this;}
		NullableValue& operator=(void* p){if(p==NULL){mHasValue=false;}else{MEDUSA_ASSERT_FAILED("Invalid assign.");} return *this;}
	public:
		bool HasValue() const { return mHasValue; }
		T& Value()
		{
			return mValue;
		}

		const T& Value()const
		{
			return mValue;
		}
		void SetValue(TParameterType val) { mValue = val; mHasValue=true;}
	private:
		T mValue;
		bool mHasValue;
	};
}
MEDUSA_END;