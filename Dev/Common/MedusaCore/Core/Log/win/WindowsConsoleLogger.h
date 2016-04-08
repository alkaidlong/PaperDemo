#pragma once
#include "Core/Log/ILogger.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

class WindowsConsoleLogger :public ILogger
{
public:
	WindowsConsoleLogger(bool isLogHeader=true);
	virtual ~WindowsConsoleLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);


};
#endif

MEDUSA_END;
