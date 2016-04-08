#include "MedusaCorePreCompiled.h"

#include "Core/Pattern/Component/IComponent.h"


MEDUSA_BEGIN;

namespace Pattern
{
	IComponent::IComponent(ComponentGroupType group,ushort priorityDelta ,void* userData)
		:mPriority(group.ToUInt()+priorityDelta),mUserData(userData)
	{
		MEDUSA_ASSERT(priorityDelta<1024,"");
	}

	bool IComponent::Update( float dt )
	{
		return true;
	}

	MEDUSA_IMPLEMENT_RTTI(IComponent,RTTIObject);
}
MEDUSA_END;