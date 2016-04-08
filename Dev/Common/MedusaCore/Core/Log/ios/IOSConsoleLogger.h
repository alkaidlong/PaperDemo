#pragma once
#include "Core/Log/ILogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_IOS

class IOSConsoleLogger :public ILogger
{
public:
	IOSConsoleLogger(bool isLogHeader=true);
	virtual ~IOSConsoleLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);


};

#endif
MEDUSA_END;
