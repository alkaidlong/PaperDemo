#include "MedusaCorePreCompiled.h"
#include "DependencyProperty.h"
#include "Core/Math/MathHeader.h"
MEDUSA_BEGIN;

namespace Pattern
{
	void DependencyProperty::Uninitialize()
	{
		SAFE_DELETE_DICTIONARY_VALUE(mRegisteredProperties);
	}

	DependencyProperty::DependencyProperty(const StringRef& propertyName,Compile::TypeInfo propertyType,const RTTIClass& ownerType,void* defaultValue)
		:mName(propertyName),mPropertyType(propertyType),mOwnerType(ownerType),mValue(defaultValue),mDefaultMetaData(NULL)
	{
		static int globalIndex=0;
		mIndex=globalIndex++;
	}

	DependencyProperty::~DependencyProperty()
	{
		SAFE_DELETE_COLLECTION(mMetaDatas);
		mDefaultMetaData=NULL;
	}

	DependencyProperty* DependencyProperty::Register(const StringRef& propertyName,Compile::TypeInfo propertyType,const RTTIClass& ownerType,void* defaultValue)
	{
		DependencyProperty* dp=new DependencyProperty(propertyName,propertyType,ownerType,defaultValue);
		mRegisteredProperties.Add(dp->GetHashCode(),dp);
		return dp;
	}

	void DependencyProperty::OverrideMetaData(DependencyPropertyMetaData* metaData)
	{
		mMetaDatas.Add(metaData);
	}

	DependencyPropertyMetaData* DependencyProperty::GetMetaData(const RTTIClass& type)
	{
		//find the most close subclass
		int distance=Math::IntMaxValue;
		DependencyPropertyMetaData* result=mDefaultMetaData;
		FOR_EACH_COLLECTION(i,mMetaDatas)
		{
			DependencyPropertyMetaData* meta=*i;
			int d=meta->GetType().GetInheritDistance(type);
			RETURN_OBJECT_IF(d==0,meta);
			if(d>0&&d<distance)
			{
				distance=d;
				result=meta;
			}
		}

		return result;
	}

	DependencyPropertyMetaData* DependencyProperty::GetMetaData(const DependencyProperty& dependencyPropery,const RTTIClass& type)
	{
		 DependencyProperty* prop=mRegisteredProperties.TryGetValueWithFailed(dependencyPropery.GetHashCode(),NULL);
		 RETURN_NULL_IF_NULL(prop);
		 return prop->GetMetaData(type);
	}

	

	Dictionary<intp,DependencyProperty*> DependencyProperty::mRegisteredProperties;

}
MEDUSA_END;