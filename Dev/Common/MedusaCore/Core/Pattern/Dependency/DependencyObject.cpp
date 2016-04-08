#include "MedusaCorePreCompiled.h"
#include "DependencyObject.h"
#include "Core/Pattern/Dependency/DependencyProperty.h"

MEDUSA_BEGIN;
namespace Pattern
{

	void* DependencyObject::GetPropertyValue(const DependencyProperty& dependencyProperty) const
	{
		FOR_EACH_COLLECTION(i,mEffectiveValues)
		{
			DependencyEffectiveValue* value=*i;
			if (value->GetPropertyIndex()==dependencyProperty.GetIndex())
			{
				return value->GetValue();
			}
		}

		DependencyPropertyMetaData* metadata=DependencyProperty::GetMetaData(dependencyProperty,this->GetRTTIClass());
		RETURN_NULL_IF_NULL(metadata);
		return metadata->GetValue();

	}

	void DependencyObject::SetPropertyValue(const DependencyProperty& dependencyProperty,void* value)
	{
		FOR_EACH_COLLECTION(i,mEffectiveValues)
		{
			DependencyEffectiveValue* value=*i;
			if (value->GetPropertyIndex()==dependencyProperty.GetIndex())
			{
				value->SetValue(value);
				return;
			}
		}

		DependencyEffectiveValue* effectiveValue=new DependencyEffectiveValue(dependencyProperty.GetIndex(),value);
		mEffectiveValues.Add(effectiveValue);
	}

	MEDUSA_IMPLEMENT_RTTI_ROOT(DependencyObject);

}
MEDUSA_END;