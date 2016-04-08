#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeInfo.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class DependencyPropertyMetaData
	{
	public:
		DependencyPropertyMetaData(const RTTIClass& type,void* value):mType(type),mValue(value){}
		virtual ~DependencyPropertyMetaData(){}
		const RTTIClass& GetType() const { return mType; }
		void* GetValue() const { return mValue; }

	private:
		const RTTIClass& mType;
		void* mValue;
	};
}

MEDUSA_END;