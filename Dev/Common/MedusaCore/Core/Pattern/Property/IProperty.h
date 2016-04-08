#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename T>
	class IProperty
	{
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	public:
		IProperty(TParameterType defaultValue):mValue(defaultValue){}
		IProperty(){}
		const T& GetValue()const{return mValue;}
		void SetValue(TParameterType val)
		{
			OnChanged(mValue,val);
			mValue=val;
		}

		Pattern::Event<void (TParameterType oldValue,TParameterType newValue )> OnChanged;
	private:
		T mValue;
	};
}

MEDUSA_END;