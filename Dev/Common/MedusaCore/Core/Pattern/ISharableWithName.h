#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/ISharable.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;
namespace Pattern
{
	class ISharableWithName:public Pattern::ISharable
	{
	public:
		ISharableWithName(const StringRef& name=StringRef::Empty):mName(name){}
		virtual ~ISharableWithName(void){}

		StringRef GetName() const { return mName; }
		void SetName(const StringRef& name){mName=name;}
		bool HasName()const{return !mName.IsEmpty();}
	protected:
		HeapString mName;
	};
}
MEDUSA_END;