#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeInfo.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/Dictionary.h"
#include "DependencyPropertyMetaData.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/RTTI/RTTIClass.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class DependencyProperty
	{
	public:
		DependencyProperty(const StringRef& propertyName,Compile::TypeInfo propertyType,const RTTIClass& ownerType,void* defaultValue);
		~DependencyProperty();
		static DependencyProperty* Register(const StringRef& propertyName,Compile::TypeInfo propertyType,const RTTIClass& ownerType,void* defaultValue);
		static DependencyPropertyMetaData* GetMetaData(const DependencyProperty& dependencyPropery,const RTTIClass& type);

		static void Uninitialize();
	public:
		intp GetHashCode()const{return mName.GetHashCode()^mOwnerType.GetHashCode();}
		void OverrideMetaData(DependencyPropertyMetaData* metaData);
		DependencyPropertyMetaData* GetMetaData(const RTTIClass& type);
		int GetIndex() const { return mIndex; }

	private:
		StringRef mName;
		Compile::TypeInfo mPropertyType;
		const RTTIClass& mOwnerType;
		void* mValue;
		int mIndex;
		DependencyPropertyMetaData* mDefaultMetaData;
		List<DependencyPropertyMetaData*> mMetaDatas;

		static Dictionary<intp,DependencyProperty*> mRegisteredProperties;
	};
}

MEDUSA_END;