#pragma once
#include "Core/Log/ILogger.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_ANDROID

class AndroidTraceLogger :public ILogger
{
public:
	AndroidTraceLogger(bool isLogHeader=true);
	virtual ~AndroidTraceLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);


};
#endif

MEDUSA_END;
