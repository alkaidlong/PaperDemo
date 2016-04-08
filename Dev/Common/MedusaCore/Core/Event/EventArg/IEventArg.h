#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

class IEventArg:public Pattern::RTTIObject
{
	MEDUSA_DECLARE_RTTI(IEventArg);
public:
	IEventArg():Handled(false){}
	virtual ~IEventArg(void){}
public:
	const static IEventArg Empty;
	volatile bool Handled;
};


typedef Pattern::Delegate<void (void* sender,IEventArg&)> EventHandler;

MEDUSA_END;