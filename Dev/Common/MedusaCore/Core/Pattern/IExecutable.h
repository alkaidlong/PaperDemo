#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;
namespace Pattern
{
	struct IExecutable
	{
		virtual void Execute()=0;
		virtual ~IExecutable(){}
	};
}

MEDUSA_END;
