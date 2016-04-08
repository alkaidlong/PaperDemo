#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class BusinessPlatformLoginEventArg:public IEventArg
{
public:
	BusinessPlatformLoginEventArg();
	virtual ~BusinessPlatformLoginEventArg(void);
public:
	bool IsLogined;
	bool IsGuestLogined;
	bool IsGuestRegistered;
	HeapString ErrorMessage;
};

MEDUSA_END;
