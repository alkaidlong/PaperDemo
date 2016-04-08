#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/IO/Updater/UpdaterDefines.h"

MEDUSA_BEGIN;
class ServerStatusEventArg:public IEventArg
{
public:
	ServerStatusEventArg(ResourceCheckingResult result)
		:mResult(result)
	{

	}
	virtual ~ServerStatusEventArg(void){}
	ResourceCheckingResult GetResult() const { return mResult; }
	void SetResult(ResourceCheckingResult val) { mResult = val; }

protected:
	ResourceCheckingResult mResult;
};

MEDUSA_END;