#pragma  once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class IInitializable
	{
	public:
		virtual bool Initialize(){return true;}
		virtual bool Uninitialize(){return true;}
	};
}

MEDUSA_END;