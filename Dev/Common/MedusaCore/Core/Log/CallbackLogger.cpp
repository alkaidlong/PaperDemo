#include "MedusaCorePreCompiled.h"
#include "CallbackLogger.h"

MEDUSA_BEGIN;

CallbackLogger::CallbackLogger(LogCallback callback,bool isLogHeader/*=true*/):ILogger(isLogHeader),mCallback(callback)
{
}


CallbackLogger::~CallbackLogger(void)
{
}

void CallbackLogger::OutputLogString( StringRef inString )
{
	if (mCallback!=NULL)
	{
		mCallback((char*)inString.c_str());
	}
}


MEDUSA_END;
