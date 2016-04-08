#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class BusinessPlatformPayEventArg:public IEventArg
{
public:
	enum class PayErrorCode
	{
		UserCancel=-4,
		NetworkFailed=-3,
		ServerReturnError=-2,
		OtherFailed=-1,
		Success=0,
		OrderEstablished=1,

	};
public:
	BusinessPlatformPayEventArg();
	virtual ~BusinessPlatformPayEventArg(void);
	bool IsSuccess()const{return ErrorCode==PayErrorCode::Success||ErrorCode==PayErrorCode::OrderEstablished;}
public:
	PayErrorCode ErrorCode;

	HeapString OrderSerial;
	HeapString ProductId;
	HeapString ProductName;
	float Price;
	float OriginalPrice;
	uint Count;
	HeapString Description;
};

MEDUSA_END;
