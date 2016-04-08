#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename T>
	struct ICopyFrom
	{
		virtual ~ICopyFrom(){}
		virtual bool CopyFrom(const T& val)
		{
			MEDUSA_ASSERT_NOT_IMPLEMENT();
			return false;
		}
	};
}

MEDUSA_END;