#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;
namespace Pattern
{
	struct IUpdatable
	{
		virtual bool Update(float dt)=0;
		virtual ~IUpdatable(){}
	};
}

MEDUSA_END;
