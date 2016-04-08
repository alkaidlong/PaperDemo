#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/IExecutable.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;


template<typename TSender,typename TEventArg>
struct WorkItem:public Pattern::IExecutable
{
	typedef Pattern::Delegate<void (TSender* sender,TEventArg)> HandlerType;

	WorkItem(HandlerType handler,TSender* sender,TEventArg eventArg)
		:Handler(handler),Sender(sender),EventArg(eventArg)
	{
		
	}

	virtual ~WorkItem()
	{
		
	}
	
	virtual void Execute()
	{
		Handler.Invoke(Sender,EventArg);
	}

	HandlerType Handler;
	TSender* Sender;
	TEventArg EventArg;
};
MEDUSA_END;
