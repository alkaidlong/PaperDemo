#include "MedusaCorePreCompiled.h"

#include "Core/Pattern/RTTI/RTTIClass.h"


MEDUSA_BEGIN;

namespace Pattern
{
	int RTTIClass::GetInheritDistance(const RTTIClass* baseClass) const
	{
		RETURN_ZERO_IF_EQUAL(this,baseClass);
		const RTTIClass* tryBaseClass=mBaseClass;
		int distance=1;
		while (tryBaseClass!=NULL&&tryBaseClass!=baseClass)
		{
			tryBaseClass=tryBaseClass->GetBaseClass();
			++distance;
		}

		return tryBaseClass!=NULL?distance:-1;
	}

	int RTTIClass::GetInheritDistance(const RTTIClass& baseClass) const
	{
		return GetInheritDistance(&baseClass);
	}

}
MEDUSA_END;