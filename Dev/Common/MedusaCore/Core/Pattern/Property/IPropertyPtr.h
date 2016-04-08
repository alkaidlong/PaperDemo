#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Ptr/NotNullPtr.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TClass,typename T>
	class IPropertyPtr
	{
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	public:
		IPropertyPtr(TClass* obj,T TClass::* val):mObj(obj),mValue(val){}
		const T& GetValue()const{return mObj->*mValue;}
		void SetValue(TParameterType val)
		{
			OnChanged(mObj->*mValue,val);
			mObj->*mValue=val;
		}

		Pattern::Event<void (TParameterType oldValue,TParameterType newValue )> OnChanged;
	private:
		TClass* mObj;
		T TClass::* mValue;
	};
}

MEDUSA_END;