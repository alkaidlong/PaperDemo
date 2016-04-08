#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename T>
	struct IClone
	{
		virtual ~IClone(){}
		virtual T* Clone() const
		{
			MEDUSA_ASSERT_NOT_IMPLEMENT();
			return NULL;
		}
	};
}

MEDUSA_END;