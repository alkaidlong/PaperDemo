#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/ComponentList.h"


MEDUSA_BEGIN;

namespace Pattern
{
	
	ComponentList::ComponentList()
	{
	}

	ComponentList::~ComponentList()
	{
		ClearComponents();
	}

	void ComponentList::ClearComponents()
	{
		FOR_EACH_COLLECTION(i,*this)
		{
			IComponent* component=*i;
			if (component->GetUserData()!=NULL)
			{
				SAFE_DELETE(component);
			}
		}
		Clear();
	}

	IComponent* ComponentList::GetComponent( StringRef name )
	{
		/*FOR_EACH_COLLECTION(i,mComponents)
		{
		IComponent* component=*i;
		if (component->GetName()==name)
		{
		return component;
		}
		}*/
		return NULL;
	}

	void ComponentList::RemoveComponent( StringRef name )
	{
		/*FOR_EACH_COLLECTION(i,mComponents)
		{
		IComponent* component=*i;
		if (component->GetName()==name)
		{
		mComponents.RemoveAt(i);

		if (!component->IsManaged())
		{
		SAFE_DELETE(component);
		}
		break;
		}
		}*/
	}

}
MEDUSA_END;