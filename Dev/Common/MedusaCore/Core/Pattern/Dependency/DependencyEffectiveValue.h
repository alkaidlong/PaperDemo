#pragma  once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class DependencyEffectiveValue
	{
	public:
		DependencyEffectiveValue(int propertyIndex,void* value):mPropertyIndex(propertyIndex),mValue(value){}
		virtual ~DependencyEffectiveValue(){}

	public:
		int GetPropertyIndex() const { return mPropertyIndex; }
		void SetPropertyIndex(int val) { mPropertyIndex = val; }

		void* GetValue() const { return mValue; }
		void SetValue(void* val) { mValue = val; }
	private:
		int mPropertyIndex;
		void* mValue;
	};
}

MEDUSA_END;