#pragma  once
#include "MedusaCorePreCompiled.h"
#include "DependencyEffectiveValue.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class DependencyObject:public Pattern::RTTIObject
	{
		MEDUSA_DECLARE_RTTI(DependencyObject);
	public:
		DependencyObject(){}
		virtual ~DependencyObject(){}

	public:
		void* GetPropertyValue(const DependencyProperty& dependencyProperty)const;
		void SetPropertyValue(const DependencyProperty& dependencyProperty,void* value);

	private:
		List<DependencyEffectiveValue*> mEffectiveValues;
	};
}

MEDUSA_END;