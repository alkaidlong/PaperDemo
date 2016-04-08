#pragma once
#include "Core/Log/ILogger.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_LINUX

class LinuxConsoleLogger :public ILogger
{
public:
	LinuxConsoleLogger(bool isLogHeader=true);
	virtual ~LinuxConsoleLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);


};
#endif

MEDUSA_END;
