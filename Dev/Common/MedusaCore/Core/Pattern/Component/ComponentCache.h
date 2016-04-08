#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IComponent.h"



MEDUSA_BEGIN;

namespace Pattern
{
	class ComponentCache
	{
	private:
		ComponentCache(){}
		~ComponentCache(){}
	public:
		static ComponentCache& Instance()
		{
			static ComponentCache factory;
			return factory;
		}
	};
}
MEDUSA_END;